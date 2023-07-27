cmake_minimum_required(VERSION 3.13)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Physx-2D)
message("Setting up the workspace ${PROJECT_NAME}")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set(OUT_DIR "${CMAKE_BINARY_DIR}/bin/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")

# Set build directory for Physx2D library
set(Physx2D_BUILD_DIR "${OUT_DIR}/Physx2D-${CMAKE_BUILD_TYPE}")
file(MAKE_DIRECTORY ${Physx2D_BUILD_DIR})
add_subdirectory(Physx2D ${Physx2D_BUILD_DIR})

# Set build directory for SandBox project
set(SandBox_BUILD_DIR "${OUT_DIR}/SandBox-${CMAKE_BUILD_TYPE}")
file(MAKE_DIRECTORY ${SandBox_BUILD_DIR})
add_subdirectory(SandBox ${SandBox_BUILD_DIR})
