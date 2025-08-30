cmake_minimum_required(VERSION 4.0)
project(raytracing2D)

set(CMAKE_CXX_STANDARD 23)

add_executable(raytracing2D main.cpp
        TPhotonRay.cpp
        TPhotonRay.h
        TGeometry.cpp
        TGeometry.h)


# Dependencies
include(FetchContent)
set(RAYLIB_VERSION 5.0)
FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
        FIND_PACKAGE_ARGS ${RAYLIB_VERSION} EXACT
)

# Removes examples
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")


#Fetches content of raylib and adds to the project files
FetchContent_MakeAvailable(raylib)

#Links libraries to the project
target_link_libraries(${PROJECT_NAME} raylib)