cmake_minimum_required(VERSION 3.10)
project(fsdb)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

option(BUILD_TESTS "build tests?" ON)
option(USE_COMMON "use ra-common library?" ON)

file(GLOB SRC src/*.cpp)
add_library(fsdb ${SRC})

target_link_directories(fsdb PUBLIC include)

if(USE_COMMON)
    add_subdirectory(common)
    target_link_libraries(fsdb ra-common)
endif()

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

