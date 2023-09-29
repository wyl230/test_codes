cmake_minimum_required(VERSION 3.17)

# ---------------------------------------------------------------------------------------------------
# 1. set name
project(test)
# message("my_variable: ${PROJECT_SOURCE_DIR}/http_lib")

# 1. set compiler
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add compile options
add_compile_options(-Wall -Wextra)

set(CMAKE_THREAD_PREFER_PTHREAD ON)
# add_executable(test main.c) 如果有头文件，可以将它们包含在项目中
add_executable(test main.cpp)
target_include_directories(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../time)

# include_directories(/home/wyl/ln/test/cpp)

#
# # 添加http库 add_library(http_lib STATIC include/http_lib/http_lib.c
# include/http_lib/mongoose.c)
#
# target_include_directories(http_lib PUBLIC ${PROJECT_SOURCE_DIR}/include )
#
find_package(Threads REQUIRED)
link_directories(${CMAKE_SOURCE_DIR})
#
target_link_libraries(test PRIVATE Threads::Threads)
# target_link_libraries(test PRIVATE http_lib)
#
# https://kingsamchen.github.io/2019/08/10/asio-cmake-package-wrapper/
include(FetchContent)

FetchContent_Declare(
  asio-cmake
  GIT_REPOSITORY https://github.com/kingsamchen/asio-cmake.git
  GIT_TAG origin/master)

# Specify asio version
set(ASIO_CMAKE_ASIO_TAG asio-1-12-2)
FetchContent_MakeAvailable(asio-cmake)

# ...

target_link_libraries(test PRIVATE asio)
