cmake_minimum_required(VERSION 3.28)
project(audiorev C)

set(CMAKE_C_STANDARD 11)

add_executable(audiorev main.c tinywav.h
        tinywav.c)
