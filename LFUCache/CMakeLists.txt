cmake_minimum_required(VERSION 3.12)
project(LFUCache VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(COMMON_SOURCES
    src/main.cpp
    src/utils.cpp
)

add_executable(LFUCache
    ${COMMON_SOURCES}
)

target_include_directories(LFUCache PRIVATE headers)

if(WIN32)
    target_compile_definitions(LFUCache PRIVATE IS_WINDOWS)
elseif(UNIX AND NOT APPLE)
    target_compile_definitions(LFUCache PRIVATE IS_LINUX)
elseif(APPLE)
    target_compile_definitions(LFUCache PRIVATE IS_MACOS)
endif()

if(WIN32)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

enable_testing()
include(CTest)

function(add_lfu_test test_name)
    message(STATUS "Adding test: ${test_name}")
    add_test(NAME ${test_name}
        COMMAND ${CMAKE_COMMAND}
            -DTEST_PROGRAM=$<TARGET_FILE:LFUCache>
            -DTEST_INPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/${test_name}.dat
            -DTEST_OUTPUT=${CMAKE_CURRENT_BINARY_DIR}/tests/${test_name}.out
            -DTEST_EXPECTED=${CMAKE_CURRENT_SOURCE_DIR}/tests/${test_name}.ans
            -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/RunTest.cmake
    )

    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/tests)
endfunction()

file(GLOB test_files "tests/*.dat")
message(STATUS "Found test files: ${test_files}")

foreach(test_file ${test_files})
    get_filename_component(test_name ${test_file} NAME_WE)
    message(STATUS "Processing test: ${test_name} from file: ${test_file}")
    add_lfu_test(${test_name})
endforeach()

add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS LFUCache
    COMMENT "Running tests..."
)
