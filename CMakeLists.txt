cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 17)

project(8086_Decoder VERSION 1.0)
set(8086_Decoder_VERSION 1.0)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

add_subdirectory(src)

if(BUILD_TESTING)
	add_subdirectory(tests)
endif()
