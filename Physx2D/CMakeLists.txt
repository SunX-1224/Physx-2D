cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Physx2D VERSION 1.0)

#----------- download all the submodules ---------------
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()
# ---------------check all the submodules ---------------
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
    message(FATAL_ERROR "GLFW submodule was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again")
endif()
# --------------module check finished ---------------------

file(GLOB SRC_FILES
    "external/glad/src/glad.c"
    "external/stb/src/stb_image.cpp"
    "src/**.cpp"
    "src/**.c"
)

# ------------- add all subdirectories ------------------
add_subdirectory(external/glfw)

configure_file(Physx2DConfig.h.in Physx2DConfig.h)

add_library(${PROJECT_NAME} SHARED ${SRC_FILES})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_BINARY_DIR}
    PUBLIC src
    PUBLIC external/glfw/include 
    PUBLIC external/glad/include
    PUBLIC external/stb/include
)
target_link_directories(${PROJECT_NAME}
    PRIVATE external/glfw/src
)
target_link_libraries(${PROJECT_NAME}
    glfw
)
#---------------- precompiled headers -----------------
target_precompile_headers(${PROJECT_NAME} PRIVATE src/pch.h)
set_source_files_properties(external/glad/src/glad.c external/stb/src/stb_image.cpp PROPERTIES SKIP_PRECOMPILE_HEADERS ON)

# ---------- Compiler definitions ----------------------
add_definitions(-DPHSX2D_BUILD_SHARED_LIB)
if (WIN32)
    add_definitions(-DPHSX2D_PLATFORM_WINDOWS)
elseif (LINUX)
    add_definitions(-DPHSX2D_PLATFORM_LINUX)
elseif (UNIX)
    add_definitions(-DPHSX2D_PLATFORM_UNIX)
endif()

# Setting up the installation to put shared_library on lib direcory and headers on include directory
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(DIRECTORY ${CMAKE_SOURCE_DIRECTORY}
    DESTINATION include
    FILES_MATCHING
    PATTERN "*.h"
)