cmake_minimum_required(VERSION 3.14)

# name of the project
project(Hashmap)

# invoke complilating options
add_compile_options(--std=c18 -O2)


set(SOURCE_EXE main.c)
set(SOURCE_LIB src/hashmap.c)
set(INCLUDE_DIR include)

add_library(hash STATIC ${SOURCE_LIB})
add_executable(start ${SOURCE_EXE})

target_include_directories(hash PUBLIC ${INCLUDE_DIR})
target_include_directories(start PUBLIC ${INCLUDE_DIR})

target_link_libraries(start hash)