cmake_minimum_required(VERSION 3.22)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(TicTacToe main.cpp)
