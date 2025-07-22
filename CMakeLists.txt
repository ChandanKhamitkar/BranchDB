# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Define your project name
project(BranchDB CXX)

set(CMAKE_CXX_STANDARD 17) # Use C++17 for std::optional
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Define source files for Executables
set(SRC_FILES
    src/main.cpp
    src/database.cpp
)

# Add an Executabale target
add_executable(BranchDB ${SRC_FILES})

target_include_directories(BranchDB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)