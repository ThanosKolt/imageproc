cmake_minimum_required(VERSION 3.20)
project(imageproc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(imageproc
    src/third_party/stb_impl.cpp
    src/io.cpp
    src/image.cpp
    src/filters.cpp
    src/parser.cpp
    src/command.cpp
    src/pixelwindow.cpp
    src/exceptions.cpp
)

target_include_directories(imageproc PUBLIC include third_party)

add_executable(imgproc src/main.cpp)
target_link_libraries(imgproc PRIVATE imageproc)

# Google Test
add_subdirectory(third_party/googletest)

add_executable(tests 
    tests/tests.cpp
    tests/test_pixelwindow.cpp
)

target_link_libraries(tests PRIVATE imageproc gtest_main)
