cmake_minimum_required(VERSION 3.10)
project(LP-AED C)

set(CMAKE_C_STANDARD 17)

add_executable(LP-AED main.c
        1.4.h
        1.5.h
        Previous.c
        1.4.c
        1.5.c)
