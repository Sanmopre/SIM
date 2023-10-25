# FILEPATH: /home/sanmopre/silicon/CMakeLists.txt

cmake_minimum_required(VERSION 3.0)

project(MyProject)
set(CMAKE_PREFIX_PATH "/home/sanmopre/vcpkg/installed/x64-linux")
find_package(raylib CONFIG REQUIRED)

# Add executable and link raylib library
add_executable(MyExecutable src/main.cpp)

target_link_libraries(MyExecutable PRIVATE raylib)
