cmake_minimum_required(VERSION 3.20)
project(ImageProc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(ImageProc 
    src/main.cpp
    src/third_party/stb_impl.cpp
    src/io.cpp
    src/image.cpp
    src/filters/negative.cpp
)

target_include_directories(ImageProc PRIVATE third_party)
target_include_directories(ImageProc PRIVATE src)

# Google Test
add_subdirectory(third_party/googletest)

add_executable(tests tests/test_main.cpp)
target_link_libraries(tests gtest_main)
target_include_directories(tests PRIVATE third_party)