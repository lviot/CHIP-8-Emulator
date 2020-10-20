cmake_minimum_required(VERSION 3.10)

project(CHIP_8 C)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED)

include_directories(./include ${SDL2_INCLUDE_DIR})

add_executable(CHIP_8
        ${SDL_LIBRARY}
        srcs/main.c
        srcs/logger.c
        srcs/opcodes.c
        include/opcode.h
        include/font.h
        srcs/core.c
        srcs/graphics.c
        srcs/keyboard.c
        srcs/utils.c
        srcs/audio.c)

target_link_libraries(CHIP_8 ${CONAN_LIBS})
