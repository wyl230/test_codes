cmake_minimum_required (VERSION 3.10.0)
project (bench_mark)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_PREFIX_PATH "/home/wyl/ln/test/cpp/benchmark/install")

find_package(sltbench REQUIRED)

find_package(sltbench REQUIRED)
add_executable(sltbench_examples
	# custom_reporter.cpp
	# demo.cpp
	# function_with_args.cpp
	# function_with_args_generator.cpp
	# function_with_exception.cpp
	# function_with_fixture.cpp
	# function_with_fixture_and_args.cpp
	# function_with_fixture_and_args_generator.cpp
	# function_with_fixture_and_lazy_args_generator.cpp
	# function_with_fixture_builder.cpp
	# function_with_fixture_builder_and_args.cpp
	# function_with_fixture_builder_and_args_generator.cpp
	# function_with_fixture_builder_and_lazy_args_generator.cpp
	# function_with_lazy_args_generator.cpp
	main.cpp
  compare_functions.cpp)
	# simple_function.cpp)

add_dependencies(sltbench_examples sltbench)

set_target_properties(sltbench_examples PROPERTIES
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO)

target_link_libraries(sltbench_examples PRIVATE sltbench)
