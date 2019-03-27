cmake_minimum_required(VERSION 3.13)
project(fsdb)

if("${TARGET_CPU}" STREQUAL "")
	set(TARGET_CPU ${CMAKE_HOST_SYSTEM_PROCESSOR})
endif()

string(TOLOWER "${TARGET_CPU}" TARGET_CPU)

if("${TARGET_CPU}" STREQUAL "amd64" OR "${TARGET_CPU}" STREQUAL "x86_64")
	set(CMAKE_SIZEOF_VOID_P 8)
	set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS TRUE)
	set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB32_PATHS FALSE)
elseif("${TARGET_CPU}" STREQUAL "x86")
	set(CMAKE_SIZEOF_VOID_P 4)

	set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS FALSE)
	set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB32_PATHS TRUE)

	if(GCC)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
	endif()
else()
	message(FATAL_ERROR "Unsupported CPU: ${TARGET_CPU}")
endif()

set(CMAKE_CXX_STANDARD 11)

set(BUILD_TESTS ON CACHE BOOL "Build unit tests")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
		${PROJECT_BINARY_DIR}/bin
		CACHE PATH
		"Single directory for all"
		)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
		${PROJECT_BINARY_DIR}/bin
		CACHE PATH
		"Single directory for all"
		)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
		${PROJECT_BINARY_DIR}/lib
		CACHE PATH
		"Single directory for all"
		)

set(FSDB_SOURCES
		src/fsdb.cpp
		)

set(FSDB_HEADERS
		include/fsdb.h
		)

add_library(fsdb STATIC ${FSDB_SOURCES} ${FSDB_HEADERS})
set(FSDB_INCLUDE_DIRS include)
set(FSDB_LIBS fsdb)
target_include_directories(fsdb PUBLIC ${FSDB_INCLUDE_DIRS})

if(BUILD_TESTS)
	include(cmake/External_GTest.cmake)
	add_executable(run_all_tests
			tests/run_all_tests.cpp
			tests/ut_basic.cpp
			)
	target_include_directories(run_all_tests PRIVATE ${FSDB_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS})
	target_link_libraries(run_all_tests ${FSDB_LIBS} ${ARGN} gtest ${CMAKE_THREAD_LIBS_INIT})
	add_dependencies(run_all_tests gtest_ext)
	add_test(NAME unit_tests COMMAND run_all_tests)
endif()


