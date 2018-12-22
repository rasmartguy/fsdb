cmake_minimum_required(VERSION 3.7)

project(fsdb-tests)

enable_testing()

include(ExternalProject)

ExternalProject_Add(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        UPDATE_DISCONNECTED 1
        CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=$<CONFIG>
        -Dgtest_force_shared_crt=ON
        PREFIX "${CMAKE_CURRENT_BINARY_DIR}/gtest"
        INSTALL_COMMAND ""
        )

ExternalProject_Get_Property(googletest SOURCE_DIR)
set(GTEST_INCLUDE_DIRS ${SOURCE_DIR}/googletest/include)
include_directories(${GTEST_INCLUDE_DIRS})

ExternalProject_Get_Property(googletest BINARY_DIR)
set(GTEST_LIBS_DIR ${BINARY_DIR}/googlemock/gtest)


file(GLOB SRC *.cpp)
add_executable(${PROJECT_NAME} ${SRC})

set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
        )
add_dependencies(${PROJECT_NAME} googletest)
target_compile_definitions(${PROJECT_NAME}
        PRIVATE -DGTEST_INVOKED
        )
if (PLATFORM_IS_BIG_ENDIAN)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DPLATFORM_IS_BIG_ENDIAN)
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DPLATFORM_IS_LITTLE_ENDIAN)
endif()

target_link_libraries(${PROJECT_NAME}
        ${GTEST_LIBS_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest$<$<CONFIG:Debug>:d>${CMAKE_STATIC_LIBRARY_SUFFIX}
        ${GTEST_LIBS_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main$<$<CONFIG:Debug>:d>${CMAKE_STATIC_LIBRARY_SUFFIX}
        fsdb
        )
if(UNIX)
    target_link_libraries(${PROJECT_NAME} pthread)
endif()

add_test(${PROJECT_NAME} ${PROJECT_NAME})
if (AUTORUN_UNITTESTS)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${PROJECT_NAME})
endif(AUTORUN_UNITTESTS)
