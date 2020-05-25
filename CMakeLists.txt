cmake_minimum_required(VERSION 3.15)
project(untitled9 C)

set(CMAKE_C_STANDARD 99)
FIND_PACKAGE(OpenMP REQUIRED)
if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${OpenMP_C_FLAGS}")
endif()
add_executable(untitled9 main.c fonction.h)
