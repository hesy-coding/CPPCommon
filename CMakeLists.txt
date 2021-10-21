cmake_minimum_required(VERSION 3.14)
project(CPPCommon)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

include_directories(Source)
#add_library(CPPCommon library.cpp)
add_subdirectory(Source)

add_subdirectory(Example)
