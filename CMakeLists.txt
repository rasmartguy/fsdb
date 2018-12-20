cmake_minimum_required(VERSION 3.10)
project(fsdb)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

option(BUILD_TESTS "build tests?" OFF)

file(GLOB SRC src/*.cpp)
add_library(fsdb ${SRC})

target_link_directories(fsdb PUBLIC include)


if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

