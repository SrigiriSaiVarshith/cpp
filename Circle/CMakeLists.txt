cmake_minimum_required(VERSION 3.15)
project(TinyRenderer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    circle.cpp
    tgaimage.cpp
)

# Executable target
add_executable(main ${SOURCES})

# Target-specific include directories (current directory for tgaimage.h)
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})