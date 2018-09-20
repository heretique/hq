cmake_minimum_required(VERSION 3.5)
project(hq VERSION 0.1.0 LANGUAGES CXX)

add_library(hq "")
target_sources(hq
    PRIVATE
        src/FreelistAllocator.cpp
        src/Hq.cpp
        src/LinearAllocator.cpp
        src/JobManager.cpp
        src/PoolAllocator.cpp
        src/ProxyAllocator.cpp
        src/Rng.cpp
        src/StackAllocator.cpp
        src/StringHash.cpp
    PUBLIC
        include/Hq/Allocator.h
        include/Hq/CompileMurmur.h
        include/Hq/concurrentqueue.h
        include/Hq/DynFreeList.h
        include/Hq/FreeList.h
        include/Hq/FreelistAllocator.h
        include/Hq/Handle.h
        include/Hq/Hash.h
        include/Hq/Hq.h
        include/Hq/IdPool.h
        include/Hq/JobManager.h
        include/Hq/LinearAllocator.h
        include/Hq/NonCopyable.h
        include/Hq/PackUtils.h
        include/Hq/PoolAllocator.h
        include/Hq/PrintContainers.h
        include/Hq/ProxyAllocator.h
        include/Hq/Rng.h
        include/Hq/SpinLock.h
        include/Hq/StackAllocator.h
        include/Hq/Streams.h
        include/Hq/StringHash.h
        include/Hq/PrintContainers.h
        include/Hq/Types.h)

target_include_directories(hq
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_compile_features(hq PUBLIC cxx_std_14)
