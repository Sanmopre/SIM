cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

project(MyProject)

if(WIN32)
    set(CMAKE_PREFIX_PATH "D:/Repos/vcpkg-good/installed/x64-windows")
else()
    set(CMAKE_PREFIX_PATH "/home/sanmopre/vcpkg/installed/x64-linux")
endif()


find_package(nlohmann_json CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

# Add all .cpp files under the src folder
file(GLOB SOURCES "src/*.cpp")

# Add executable and link raylib library
add_executable(simulator ${SOURCES})

target_link_libraries(simulator PRIVATE glm::glm)
target_link_libraries(simulator PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(simulator PRIVATE glfw)
target_link_libraries(simulator PRIVATE glad::glad)


