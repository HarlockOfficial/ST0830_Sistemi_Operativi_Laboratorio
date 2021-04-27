cmake_minimum_required(VERSION 3.19)
project(caesar_cipher_files C)

set(CMAKE_C_STANDARD 11)

add_executable(caesar_cipher_files main.c caesar.c caesar.h constraints.h)
