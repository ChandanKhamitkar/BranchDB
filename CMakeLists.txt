# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Define your project name
project(BranchDB CXX)

# Add source directory
aux_source_directory(src SRC_FILES)

# Add an Executabale target
add_executable(BranchDB ${SRC_FILES})