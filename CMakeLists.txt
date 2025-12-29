cmake_minimum_required(VERSION 3.10)
project(LP-AED C)

set(CMAKE_C_STANDARD 17)

add_executable(LP-AED main.c
        matriz_strl.c
        1.4.h
        1.5.h
        1.3.c
        1.4.c
        1.5.c
        text_io.c
        1.6.c
        2.1.c
)
