cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)

project(range)

set(headers
	include/range/range.hpp
)

set(sources
)

add_library(range ${headers} ${sources})
target_include_directories(range PUBLIC include)
set_target_properties(range PROPERTIES LINKER_LANGUAGE CXX)

enable_testing()
add_subdirectory(tests)
