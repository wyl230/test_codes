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
# add_executable(test main.c)
add_executable(test main.cpp)
# 如果有头文件，可以将它们包含在项目中
target_include_directories(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../time)
target_include_directories(test
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/openthread/src)

add_library(mini_openthread STATIC
            ${CMAKE_CURRENT_SOURCE_DIR}/openthread/src/openthread.cpp)
target_link_libraries(test PRIVATE mini_openthread)
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
