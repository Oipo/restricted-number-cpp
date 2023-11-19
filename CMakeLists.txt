cmake_minimum_required(VERSION 3.12)
project(restricted_number_cpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE CXX STANDARD REQUIRED ON)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external//Catch2)
#enable string_view support in catch2
target_compile_features(Catch2 PRIVATE cxx_std_20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external//Catch2/extras")

include(CTest)
include(Catch)

enable_testing()

set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/external/)

add_executable(restricted_number_cpp_tests tests/restricted-numbers-tests.cpp)
add_test(NAME restricted_number_cpp_tests COMMAND restricted_number_cpp_tests)

target_link_libraries(restricted_number_cpp_tests Catch2::Catch2WithMain)
