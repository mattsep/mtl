cmake_minimum_required(VERSION 3.11)

project(mtl
    LANGUAGES CXX
    VERSION 0.1.0
)

add_library(mtl INTERFACE)
target_include_directories(mtl INTERFACE include)