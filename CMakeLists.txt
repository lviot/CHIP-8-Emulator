cmake_minimum_required(VERSION 3.10)
project(CHIP_8 C)

set(CMAKE_C_STANDARD 11)

include_directories(headers)

add_executable(CHIP_8
        headers/chip8.h
        srcs/main.c srcs/opcodes.c headers/opcode.h headers/font.h srcs/font.c srcs/core.c)