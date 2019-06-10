cmake_minimum_required(VERSION 3.13)
project(fsdb CXX)

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

set(BUILD_TESTS OFF CACHE BOOL "Build unit tests")

set(FSDB_SOURCES
		src/fsdb.cpp
		)

set(FSDB_HEADERS
		include/fsdb.h
		)

add_library(fsdb STATIC ${FSDB_SOURCES})
set_property(TARGET fsdb PROPERTY CXX_STANDARD 11)
set(FSDB_INCLUDE_DIRS include)
set(FSDB_LIBS fsdb)
target_include_directories(fsdb PUBLIC ${FSDB_INCLUDE_DIRS})
link_directories(${CMAKE_BINARY_DIR})

if(BUILD_TESTS)
	configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
	execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
			RESULT_VARIABLE result
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
	if(result)
		message(FATAL_ERROR "CMake step for googletest failed: ${result}")
	endif()
	execute_process(COMMAND ${CMAKE_COMMAND} --build .
			RESULT_VARIABLE result
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
	if(result)
		message(FATAL_ERROR "Build step for googletest failed: ${result}")
	endif()

	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

	add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
			${CMAKE_CURRENT_BINARY_DIR}/googletest-build
			EXCLUDE_FROM_ALL)

    include_directories("${gtest_SOURCE_DIR}/include")
    include_directories("${gmock_SOURCE_DIR}/include")

	add_executable(run_all_tests
			#tests/run_all_tests.cpp
			tests/ut_basic.cpp
			)
	target_include_directories(run_all_tests PRIVATE ${FSDB_INCLUDE_DIRS})
	target_link_libraries(run_all_tests fsdb gtest_main gmock_main)
	enable_testing()
	add_test(NAME unit_tests COMMAND run_all_tests)
endif()

