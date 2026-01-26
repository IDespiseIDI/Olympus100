cmake_minimum_required(VERSION 3.10)
project(Olympus100 VERSION 0.1.0.0)

set(SOURCE_FILES src/cpu/opcode.cpp src/fw/main.cpp src/ram/ram.cpp src/disk/disk.cpp
)

include_directories(include)

add_executable(Olympus100 ${SOURCE_FILES})