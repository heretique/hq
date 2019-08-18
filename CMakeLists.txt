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
        src/Math/Math.cpp
        src/Math/Utils.cpp
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/Allocator.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/CompileMurmur.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/concurrentqueue.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/DynFreeList.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/FreeList.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/FreelistAllocator.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/Handle.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/Hash.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/Hq.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/IdPool.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/JobManager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/LinearAllocator.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/NonCopyable.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/PackUtils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/PoolAllocator.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/PrintContainers.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/ProxyAllocator.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/Rng.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/SpinLock.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/StackAllocator.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/Streams.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/StringHash.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/PrintContainers.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/Types.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/Utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/Math/AABB.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/Math/MathTypes.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/Math/Math.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/Math/Vector.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/Math/Ray.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Hq/Math/Utils.h)

target_include_directories(hq
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_compile_features(hq PUBLIC cxx_std_14)
