cmake_minimum_required(VERSION 3.0)

project(MyProject)
set(CMAKE_PREFIX_PATH "/home/sanmopre/vcpkg/installed/x64-linux")
find_package(raylib CONFIG REQUIRED)

# Add all .cpp files under the src folder
file(GLOB SOURCES "src/*.cpp")

# Add executable and link raylib library
add_executable(MyExecutable ${SOURCES})

target_link_libraries(MyExecutable PRIVATE raylib)
