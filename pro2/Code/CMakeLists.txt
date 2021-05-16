cmake_minimum_required(VERSION 3.19)
project(pro2)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(. ALL_SRCS)
add_executable(pro2 ${ALL_SRCS})