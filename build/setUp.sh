#!/bin/sh

# Set the path to your Vcpkg directory
VCPKG_ROOT="/opt/vcpkg"

echo "Installing libraries with Vcpkg"
"$VCPKG_ROOT/vcpkg" install physx glfw3 glad glm spdlog
if [ $? -ne 0 ]; then
    echo "Error: Failed to install libraries."
    exit 1
fi

echo "Integrating libraries with the project"
"$VCPKG_ROOT/vcpkg" integrate install

echo "CMAKE"
cmake -DCMAKE_BUILD_TYPE=Debug "-GUnix Makefiles" -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" ..

make

echo "Done!"
