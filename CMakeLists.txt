cmake_minimum_required(VERSION 3.10)

project(CHIP_8 C)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED)

include_directories(headers ${SDL2_INCLUDE_DIR})

add_executable(CHIP_8
        ${SDL_LIBRARY}
        srcs/main.c srcs/logger.c srcs/opcodes.c headers/opcode.h headers/font.h srcs/core.c srcs/graphics.c headers/graphics.h headers/types.h headers/keyboard.h srcs/keyboard.c srcs/utils.c srcs/audio.c headers/logger.h)

target_link_libraries(CHIP_8 ${CONAN_LIBS})
