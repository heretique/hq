add_executable(tests "")
target_sources(tests PRIVATE
    catch.cpp
    math.cpp)

target_include_directories(tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include)

target_link_libraries(tests hq)
