cmake_minimum_required(VERSION 3.10)

project(BinaryTreeSearch)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCE source/*.cpp)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${SOURCE})
target_sources(${PROJECT_NAME} PRIVATE ../Lab2/source/BinaryTree.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE ../Lab2/include)
