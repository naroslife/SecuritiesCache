cmake_minimum_required(VERSION 3.20)
project(SecuritiesCache)

set(CMAKE_CXX_STANDARD 14)
set(Boost_INCLUDE_DIR C:/Users/Asus/Downloads/Utilities/boost_1_77_0)

add_subdirectory(GoogleTest)
add_library(SecuritiesCache Cache.cpp Cache.h Order.cpp Order.h)
target_include_directories(SecuritiesCache PUBLIC ${Boost_INCLUDE_DIR})