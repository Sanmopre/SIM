cmake_minimum_required(VERSION 3.0)

project(MyProject)

if(WIN32)
    set(CMAKE_PREFIX_PATH "D:/Repos/vcpkg/installed/x64-windows")
else()
    set(CMAKE_PREFIX_PATH "/media/sanmopre/Nuevo vol/Repos/vcpkg/installed/x64-linux")
endif()


find_package(raylib CONFIG REQUIRED)
find_package(unofficial-noise CONFIG REQUIRED)



# Add all .cpp files under the src folder
file(GLOB SOURCES "src/*.cpp")

# Add executable and link raylib library
add_executable(MyExecutable ${SOURCES})

target_link_libraries(MyExecutable PRIVATE raylib)
target_link_libraries(MyExecutable PRIVATE unofficial::noise::noise-static)