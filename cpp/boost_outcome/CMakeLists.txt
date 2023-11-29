cmake_minimum_required(VERSION 3.17)

# ---------------------------------------------------------------------------------------------------
# 1. set name
project(test)
# message("my_variable: ${PROJECT_SOURCE_DIR}/http_lib")

# 1. set compiler
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# boost
set(Boost_INCLUDE_DIR ~/chores/usr/local/include)
set(Boost_LIBRARY_DIR ~/chores/usr/local/lib)
find_package(
  Boost
  COMPONENTS system filesystem
  REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

# boost end

# add compile options
add_compile_options(-Wall -Wextra)

set(CMAKE_THREAD_PREFER_PTHREAD ON)
# add_executable(test main.c)
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
target_link_libraries(test PRIVATE ${Boost_LIBRARIES})
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
