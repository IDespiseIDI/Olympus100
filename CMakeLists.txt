cmake_minimum_required(VERSION 3.10)
project(Olympus100 VERSION 2.0.1)

set(SOURCE_FILES src/cpu/opcode.c src/fw/main.c src/ram/ram.c src/disk/disk.c
)

include_directories(include)

add_executable(Olympus100 ${SOURCE_FILES})