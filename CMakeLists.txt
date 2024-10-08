# TO COMPILE JUST RUN ON THE ROOT DIRECTORY:
#   cmake -S . -B build -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ && cmake --build build --parallel $(nproc)
# TO CLEAN BUILD USE: cmake --build build --target clean (or rm -rfv build)

# Set the minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and C standard version
project(MIRAGE C)

# Set C Standard
set(CMAKE_C_STANDARD 23)

set(CMAKE_C_EXTENSIONS OFF)

# Force CMake to use Clang
set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)
add_compile_options(
    -O3 -ggdb -g -pg -march=native -std=c23
    -Wall -Wextra -Werror -Wshadow -Wformat -Wreturn-type -Wuninitialized
    -Wno-missing-braces -pedantic
    -fsanitize=address
)


# /usr/lib/libasan.so
# Set policy for OpenGL to prefer GLVND
cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)

# Find SDL2 and OpenGL
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

# Include directories for SDL2, OpenGL
include_directories(
    ${SDL2_INCLUDE_DIRS} 
    ${OPENGL_INCLUDE_DIR} 
)

# Add GLAD as a library
add_library(glad STATIC lib/external/GLAD/glad.c)

# Set include directories for GLAD
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/lib/external/GLAD)


# Adds CGLM Dependency
add_subdirectory(lib/external/CGLM)

# Source files
set(SOURCES
    src/main.c
    lib/internal/sources/ecglm/matrix/matrix.c
    lib/internal/sources/sdl/window/window.c
    lib/internal/sources/sdl/input/input.c
    lib/internal/sources/opengl/renderer/renderer.c
    lib/internal/sources/opengl/shaders/shaders.c
)

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Link the necessary libraries
# target_link_libraries(${LIBRARY_NAME} PRIVATE cglm_headers)
target_link_libraries(${PROJECT_NAME} asan  ${SDL2_LIBRARIES} ${OPENGL_gl_LIBRARY} glad cglm m dl)
