cmake_minimum_required(VERSION 2.8.12)
project(example)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(pybind11)

find_package(pybind11 REQUIRED)

pybind11_add_module(example example.cpp)

pybind11_add_module(list_example list_example.cpp)
