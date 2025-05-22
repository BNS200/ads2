
cmake_minimum_required(VERSION 3.10)


project(BinaryTreeProject)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


include_directories(include)


add_executable(BinaryTree
    source/BinaryTree.cpp
    source/BinaryTreeMain.cpp
)

add_library(Lab2Lib STATIC source/BinaryTree.cpp)