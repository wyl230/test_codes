cmake_minimum_required(VERSION 3.17)

# ---------------------------------------------------------------------------------------------------
# 1. set name
project(test)
# message("my_variable: ${PROJECT_SOURCE_DIR}/http_lib")

# 1. set compiler set(CMAKE_CXX_STANDARD 17)

set(Boost_NO_SYSTEM_PATHS TRUE)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -fcoroutines -fexceptions -O2 -std=c++20 -I/home/wyl/chores/usr/local/include -L/home/wyl/chores/usr/local/lib " # 后两个只是为了让clangd工具能够找到正确版本的boost，实际的boost再fetch的时候已经指定了
)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines -fno-exceptions -O0")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add compile options set(FORTE_RTTI_AND_EXCEPTIONS true)
add_compile_options(-Wall -Wextra)

set(CMAKE_THREAD_PREFER_PTHREAD ON)
# add_executable(test main.c) add_executable(test main.cpp )
add_executable(test main.cpp)
# 如果有头文件，可以将它们包含在项目中
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
# ## FetchContent # add my http_lib include(FetchContent)
#
# FetchContent_Declare( readerwriterqueue GIT_REPOSITORY
# https://github.com/cameron314/readerwriterqueue GIT_TAG           master )
#
# FetchContent_MakeAvailable(readerwriterqueue)
#
# target_link_libraries(test PUBLIC readerwriterqueue)
#
# # add json include(FetchContent)
#
# FetchContent_Declare(json URL
# https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
# FetchContent_MakeAvailable(json)
#
# target_link_libraries(test PRIVATE nlohmann_json::nlohmann_json)

# https://kingsamchen.github.io/2019/08/10/asio-cmake-package-wrapper/
include(FetchContent)

FetchContent_Declare(
  asio-cmake
  GIT_REPOSITORY https://github.com/kingsamchen/asio-cmake.git
  GIT_TAG origin/master)

# Specify asio version
set(ASIO_CMAKE_ASIO_TAG asio-1-28-0)
FetchContent_MakeAvailable(asio-cmake)

# ...

target_link_libraries(test PRIVATE asio)

# boost
set(BOOST_INCLUDE_LIBRARIES thread filesystem system program_options)
set(BOOST_ENABLE_CMAKE ON)

include(FetchContent)
FetchContent_Declare(
  Boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.83.0)
FetchContent_MakeAvailable(Boost)

target_link_libraries(test PRIVATE Boost::filesystem Boost::program_options)
