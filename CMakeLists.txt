cmake_minimum_required(VERSION 3.12)
project(restricted_number_cpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE CXX STANDARD REQUIRED ON)

enable_testing()

set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/external/)

add_executable(restricted_number_cpp_tests tests/restricted-numbers-tests.cpp)
add_test(NAME restricted_number_cpp_tests COMMAND restricted_number_cpp_tests)

include_directories("${EXTERNAL_DIR}/Catch2/single_include")