cmake_minimum_required(VERSION 3.13)
project(fsdb)

set(CMAKE_CXX_STANDARD 11)

set(BUILD_TESTS ON CACHE BOOL "Build unit tests" FORCE)

set(FSDB_SOURCES
		src/fsdb.cpp
		)

set(FSDB_HEADERS
		include/fsdb.h
		)

add_library(fsdb SHARED ${FSDB_SOURCES} ${FSDB_HEADERS})
set(FSDB_INCLUDE_DIRS include)
set(FSDB_LIBS fsdb)
target_include_directories(fsdb PUBLIC ${FSDB_INCLUDE_DIRS})

if(BUILD_TESTS)
	include(cmake/External_GTest.cmake)
	add_executable(run_all_tests
			tests/run_all_tests.cpp
			tests/ut_basic.cpp
			)
	target_include_directories(run_all_tests PRIVATE ${FSDB_INCLUDE_DIRS})
	target_link_libraries(run_all_tests ${FSDB_LIBS} ${ARGN} gtest ${CMAKE_THREAD_LIBS_INIT})
	add_dependencies(run_all_tests gtest_ext)
	add_test(NAME unit_tests COMMAND run_all_tests)
endif()


