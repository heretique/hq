cmake_minimum_required(VERSION 3.5)
project(hq VERSION 0.1.0 LANGUAGES CXX)

include(CMakeToolsHelpers OPTIONAL)

option(WITH_TESTS "Enables tests" OFF)

add_subdirectory(src)
if (WITH_TESTS)
    add_subdirectory(tests)
endif()