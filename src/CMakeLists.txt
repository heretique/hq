cmake_minimum_required(VERSION 3.5)

add_library(hq "")
target_sources(hq
    PRIVATE
        FreelistAllocator.cpp
        Hq.cpp
        LinearAllocator.cpp
        JobManager.cpp
        PoolAllocator.cpp
        ProxyAllocator.cpp
        Rng.cpp
        StackAllocator.cpp
        StringHash.cpp
        Math/Math.cpp
        Math/Utils.cpp
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Allocator.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/CompileMurmur.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/concurrentqueue.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/DynFreeList.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/FreeList.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/FreelistAllocator.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Handle.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Hash.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Hq.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/IdPool.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/JobManager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/LinearAllocator.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/NonCopyable.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/PackUtils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/PoolAllocator.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/PrintContainers.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/ProxyAllocator.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Rng.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/SpinLock.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/StackAllocator.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Streams.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/StringHash.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/PrintContainers.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Types.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/AABB.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/MathTypes.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/Math.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/Vector.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/Ray.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/Utils.h)

target_include_directories(hq
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(hq PUBLIC cxx_std_14)
