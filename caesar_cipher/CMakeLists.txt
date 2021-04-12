cmake_minimum_required(VERSION 3.19)
project(caesar_cipher C)

set(CMAKE_C_STANDARD 11)

add_executable(caesar_cipher main.c input.c input.h constraints.h caesar.c caesar.h)