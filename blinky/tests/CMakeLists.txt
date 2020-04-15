cmake_minimum_required(VERSION 3.5.0 FATAL_ERROR)

project(tests)

set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/..)

include(${PROJECT_SOURCE_DIR}/cmake/CPM_setup.cmake)


#------------------------------------------------------------------------------
# Build Settings
#------------------------------------------------------------------------------

# default settings

set(OPTIMIZE 0)
set(TEST_ALL 0)

# Include custom settings
# (if this file does not exist, copy it from config.cmake.example)
# include(${CMAKE_SOURCE_DIR}/config.cmake)

message(STATUS "Config OPTIMIZE: ${OPTIMIZE}")
message(STATUS "Config TEST_ALL: ${TEST_ALL}")


# system libraries to link, separated by ';'
set(SYSTEM_LIBRARIES m c)

# linux needs libbsd
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message(STATUS "Linux detected: linking to libbsd")
    list(APPEND SYSTEM_LIBRARIES bsd)
    set(L_FLAGS "-fmessage-length=80 -Wl,--gc-sections")
else()
    set(L_FLAGS "-fmessage-length=80 -Wl,-dead_strip")
endif()

# compile flags
set(C_FLAGS_WARN "-Wall -Wextra -Wno-unused-parameter                   \
    -Wshadow -Wpointer-arith -Winit-self -Wstrict-overflow=4            \
    -Werror=implicit-function-declaration")

    set(C_FLAGS "${C_FLAGS_WARN} -O${OPTIMIZE} -g3 -c -fmessage-length=80        \
    -fno-builtin -ffunction-sections -fdata-sections -std=gnu99         \
    -fdiagnostics-color=auto")

add_definitions("${C_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${L_FLAGS}")
set(CPM_LIBRARIES "${SYSTEM_LIBRARIES}${CPM_LIBRARIES}")


# dir where the normal project sources can be found
set(TEST_NORMAL_SOURCE_DIR   "${PROJECT_SOURCE_DIR}/src")

# dir where the test-related sources can be found
set(TEST_TESTS_SOURCE_DIR    "${CMAKE_CURRENT_SOURCE_DIR}")
add_definitions("-DTEST_SRC_DIR=\"${TEST_TESTS_SOURCE_DIR}\"")

# Enable ALL tests: runs some brute-force-like tests that take very long to complete.
add_definitions(-DTEST_ALL=${TEST_ALL})

# set specific sources: for each test <testname>,
# the sources specified by test_<testname>_src are linked in.
# Note: these are relative to TEST_NORMAL_SOURCE_DIR.

set(test_flow_src   sensors/flow.c)
set(test_crc_src   crc/crc16.c)


# all 'shared' c files: these are linked against every test.
# files that also occur in TEST_MAIN_SOURCES are automatically removed
file(GLOB TEST_SHARED_SOURCES
    RELATIVE ${TEST_TESTS_SOURCE_DIR}
    "*.c"
)

# all test 'main' files: each of these should have its own main() function.
# they are compiled and run when calling 'make tests'
file(GLOB TEST_MAIN_SOURCES
    RELATIVE ${TEST_TESTS_SOURCE_DIR}
    "*.test.c"
)

include_directories("${TEST_TESTS_SOURCE_DIR}/mocks")
#include_directories("${TEST_NORMAL_SOURCE_DIR}/sub_dir1")


CPM_AddModule("cpm_unity"
    GIT_REPOSITORY "https://github.com/JitterCompany/cpm_unity.git"
    GIT_TAG "2.3.2-9")


CPM_Finish()

