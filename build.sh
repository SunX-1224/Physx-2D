#!/bin/bash
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <build_type>"
    echo "build_type: Debug or Release"
    exit 1
fi

BUILD_TYPE=$1
BUILD_DIR="build"

PLATFORM=$(uname -s)

mkdir -p $BUILD_DIR

if [ "$PLATFORM" = "Linux" ] || [ "$PLATFORM" = "Darwin" ]; then
    # For Linux or macOS
    # cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..
    cmake -DGLFW_BUILD_DOCS=OFF -S . -B ./build -DCMAKE_BUILD_TYPE=$BUILD_TYPE -G "Unix Makefiles"
    make -C ./$BUILD_DIR
elif [[ "$PLATFORM" = *"MINGW64_NT"* ]] || [[ "$PLATFORM" = *"MSYS_NT"* ]]; then
    # For Windows using MSYS2 or similar
    # cmake -G "Ninja" -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..
    cmake -DGLFW_BUILD_DOCS=OFF -S . -B ./build -DCMAKE_BUILD_TYPE=$BUILD_TYPE -G "Visual Studio 17 2022"
    msbuild "$BUILD_DIR/Physx-2D.sln" /p:Configuration=$BUILD_TYPE
else
    echo "Unsupported platform: $PLATFORM"
    exit 1
fi
read -p "Press any key to continue"

