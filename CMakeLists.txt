cmake_minimum_required(VERSION 3.20)
project(imageproc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(imageproc 
    src/main.cpp
    src/third_party/stb_impl.cpp
    src/io.cpp
    src/image.cpp
    src/filters.cpp
    src/cli.cpp
)

target_include_directories(imageproc PRIVATE third_party)
target_include_directories(imageproc PRIVATE src)

# Google Test
add_subdirectory(third_party/googletest)

add_executable(tests 
    tests/tests.cpp
    src/third_party/stb_impl.cpp
    src/io.cpp
    src/image.cpp
    src/filters.cpp
    src/cli.cpp
)

target_link_libraries(tests gtest_main)
target_include_directories(tests PRIVATE third_party)
target_include_directories(tests PRIVATE src)