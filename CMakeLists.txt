cmake_minimum_required(VERSION 3.14)
project("FastSquareRoot")
#include(FetchContent)

################################################################
### SET C++17 STANDARD
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

################################################################
# FMT (c++20 adds majority off this as std::format)
#FetchContent_Declare(fmt
#    GIT_REPOSITORY https://github.com/fmtlib/fmt
#    GIT_TAG 8.0.1
#)
#FetchContent_MakeAvailable(fmt)

add_subdirectory(src)
