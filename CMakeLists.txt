cmake_minimum_required(VERSION 3.10)

# Project Name
project(db.c)

# Set C standard
set(CMAKE_C_STANDARD 99)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/includes)

# Source files
file(GLOB SOURCES "src/*.c")

# Executable
add_executable(db ${SOURCES})

