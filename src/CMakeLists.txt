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
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/NotImplemented.h
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
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/BasicTypes.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/AABB.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/MathTypes.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/Math.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/Plane.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/Quat.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/Line3.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/Line2.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/Mat4x4.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/Mat3x3.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/Frustum.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/Circle.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/Rect.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/Box3.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/Box2.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/Sphere.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/Ray3.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/Ray2.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/Vec4.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/Vec3.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/Vec2.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Hq/Math/Triangle.h
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