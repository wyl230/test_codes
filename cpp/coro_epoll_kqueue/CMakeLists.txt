cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -fcoroutines  -O0 -g -fsanitize=address")
# set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set the project name
project(coro_epoll)

if(UNIX AND NOT APPLE)
  add_executable(coro_epoll echo_server.cpp io_context_epoll.cpp socket.cpp)
else()
  add_executable(coro_kqueue echo_server.cpp io_context_kqueue.cpp socket.cpp)
endif()

add_compile_options(-Wall -Wextra)

# set(CMAKE_THREAD_PREFER_PTHREAD ON)

target_include_directories(coro_epoll PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(coro_epoll PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

# find_package(Threads REQUIRED) link_directories(${CMAKE_SOURCE_DIR})
# target_link_libraries(coro_epoll PRIVATE Threads::Threads)
