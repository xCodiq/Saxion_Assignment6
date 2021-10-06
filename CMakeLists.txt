cmake_minimum_required(VERSION 3.20)
project(Assignment6 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wall -Wextra -pedantic")

add_executable(Assignment6 main.c)
