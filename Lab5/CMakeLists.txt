
cmake_minimum_required(VERSION 3.10)
project(HuffmanProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES
    source/boolvector.cpp
    source/HuffmanTree.cpp
    source/HuffmanTreeMain.cpp
)

add_executable(HuffmanTreeMain ${SOURCES})

