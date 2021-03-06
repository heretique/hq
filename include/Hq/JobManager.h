#pragma once

#include "concurrentqueue.h"
#include <functional>
#include <mutex>
#include <vector>
#include <condition_variable>

namespace hq
{
struct Job;

typedef std::function<void(void*, size_t)> JobFunc;
typedef std::function<void()>              JobDoneFunc;

struct Job
{
    JobFunc func;
    void*   data;
    size_t  count;
    bool    pending {true};  // used for jobs you wait for
};

template <typename DataType, size_t Size>
class CountSplitter
{
public:
    CountSplitter() {}

    static bool split(size_t count)
    {
        return count > Size;
    }
};

template <typename DataType, size_t Size>
class DataSizeSplitter
{
public:
    DataSizeSplitter() {}

    static bool split(size_t count)
    {
        return count * sizeof(DataType) > Size;
    }
};

struct ConcurrentQueueTraits : public moodycamel::ConcurrentQueueDefaultTraits
{
    static const size_t BLOCK_SIZE = 256;  // Use bigger blocks
};

/// Job Manager
/// Supports only POD data types and random acces iterators (plain pointers)
class JobManager
{
public:
    void init();
    void release();

    // you wait for this kind of jobs
    void addJob(JobFunc func, void* data, size_t count = 1);

    template<typename FuncType, typename DataType>
    void addJob(FuncType func, DataType* data, size_t count = 1);

    // you don't wait for this kind of jobs, they'll signal you when they're done
    void addSignalingJob(JobFunc func, void* data, size_t count, JobDoneFunc callback);

    template<typename FuncType, typename DataType>
    void addSignalingJob(FuncType func, DataType* data, size_t count, JobDoneFunc callback);

    template <typename DataType, typename SplitterType>
    void parallel_for(JobFunc func, void* data, size_t count);

    void wait();

private:
    moodycamel::ConcurrentQueue<Job, ConcurrentQueueTraits> _jobQueue;
    std::vector<std::thread>                                _runners;
    size_t                                                  _cpuCount {0};
    std::atomic<size_t>                                     _pendingTasks {0};
    std::atomic_flag                                        _running;
    std::mutex                                              _hasJobsMutex;
    bool                                                    _hasJobs {false};
    std::condition_variable                                 _hasJobsCondition;
};


template<typename FuncType, typename DataType>
void JobManager::addJob(FuncType func, DataType* data, size_t count)
{
    auto jobFunc = [=](void* jobData, size_t jobCount) {
        DataType* castData = static_cast<DataType*>(jobData);
        func(castData, jobCount);
    };
    addJob(jobFunc, static_cast<void*>(data), count);
}

template<typename FuncType, typename DataType>
void JobManager::addSignalingJob(FuncType func, DataType *data, size_t count, JobDoneFunc callback)
{
    auto jobFunc = [=](void* jobData, size_t jobCount) {
        DataType* castData = static_cast<DataType*>(jobData);
        func(castData, jobCount);
    };
    addSignalingJob(jobFunc, static_cast<void*>(data), count, callback);
}

template <typename DataType, typename SplitterType>
void JobManager::parallel_for(JobFunc func, void* data, size_t count)
{
    if (SplitterType::split(count))
    {
        auto jobFunc = [=](void* splitData, size_t splitCount) {
            DataType*    castData   = static_cast<DataType*>(splitData);
            const size_t leftCount  = splitCount / 2u;
            const size_t rightCount = splitCount - leftCount;
            parallel_for<DataType, SplitterType>(func, castData, leftCount);
            parallel_for<DataType, SplitterType>(func, castData + leftCount, rightCount);
        };
        addJob(jobFunc, data, count);
    }
    else
    {
        addJob(func, data, count);
    }
}

}  // namespace hq
