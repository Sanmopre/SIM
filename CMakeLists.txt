cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

project(MyProject)

if(WIN32)
    set(CMAKE_PREFIX_PATH "D:/Repos/vcpkg-good/installed/x64-windows")
else()
    set(CMAKE_PREFIX_PATH "/media/sanmopre/Nuevo vol/Repos/vcpkg-good/installed/x64-linux")
endif()


find_package(raylib CONFIG REQUIRED)
find_package(unofficial-noise CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)


# Add all .cpp files under the src folder
file(GLOB SOURCES "src/*.cpp")

# Add executable and link raylib library
add_executable(MyExecutable ${SOURCES})

target_link_libraries(MyExecutable PRIVATE raylib)
if(WIN32)
    target_link_libraries(MyExecutable PRIVATE unofficial::noise::noise)
    target_link_libraries(MyExecutable PRIVATE nlohmann_json::nlohmann_json)
else()
    target_link_libraries(MyExecutable PRIVATE unofficial::noise::noise-static)
    target_link_libraries(MyExecutable PRIVATE nlohmann_json::nlohmann_json)
endif()
