cmake_minimum_required(VERSION 3.14)

project(Hashmap)

add_compile_options(--std=c18 -O2)

add_library(librar STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/hashmap.c)

target_include_directories(librar PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(librar PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/librar/include)