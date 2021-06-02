cmake_minimum_required(VERSION 3.19)
project(BTree C)

set(CMAKE_C_STANDARD 99)

add_executable(BTree main.c BTree.c BTree.h)