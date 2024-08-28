# cmake -DGLFW_BUILD_DOCS=OFF -S . -B ./build -G "Unix Makefiles"
PLATFORM=$(uname -s)

if [ "$PLATFORM" = "Linux" ] || [ "$PLATFORM" = "Darwin" ]; then
    # For Linux or macOS
    cmake -DGLFW_BUILD_DOCS=OFF -S . -B ./build -DCMAKE_BUILD_TYPE=$BUILD_TYPE -G "Unix Makefiles"
elif [ "$PLATFORM" = "MINGW64_NT" ] || [ "$PLATFORM" = "MSYS_NT" ]; then
    # For Windows using MSYS2 or similar
    cmake -DGLFW_BUILD_DOCS=OFF -S . -B ./build -DCMAKE_BUILD_TYPE=$BUILD_TYPE -G "Visual Studio 17 2022"
else
    echo "Unsupported platform: $PLATFORM"
    exit 1
fi
read -p "Press any key to continue"
