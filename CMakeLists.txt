# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(MyProgram)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(source/headers /usr/include/SDL2)

# Find all source files in the source/src directory
file(GLOB SRC_FILES "source/src/*.cpp")

# Create the executable
add_executable(my_program ${SRC_FILES})
#
# Link the SDL2 and SDL2_image libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

target_link_libraries(my_program SDL2 SDL2_image)
