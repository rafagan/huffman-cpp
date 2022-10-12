cmake_minimum_required(VERSION 3.3)
project(Huffman)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp Node.cpp Node.h Huffman.cpp Huffman.h utils.h)
add_executable(Huffman ${SOURCE_FILES})