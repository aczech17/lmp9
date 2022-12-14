cmake_minimum_required(VERSION 3.24)
project(lmp9 C)

set(CMAKE_C_STANDARD 11)

add_executable(lmp9 main.c backsubst.c gauss.c mat_io.c)
