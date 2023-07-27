cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(SandBox LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SRC_FILES 
    "src/*.cpp"
    "applications/*.cpp"
)
file(GLOB EXTERNALS
    "../Physx2D/external/glad/src/glad.c"
)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${EXTERNALS})

target_include_directories(${PROJECT_NAME} PRIVATE "../Physx2D")
target_link_libraries(${PROJECT_NAME} Physx2D)


# Setting up the installation to put executable in bin directory
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# Installer configs
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set(CPACK_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
include(CPack)
