cmake_minimum_required(VERSION 3.12)
project(IdealCache VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(COMMON_SOURCES
    src/main.cpp
)

add_executable(IdealCache
    # src/main.cpp
    ${COMMON_SOURCES}
)

target_include_directories(IdealCache PRIVATE headers)

if(WIN32)
    target_compile_definitions(IdealCache PRIVATE IS_WINDOWS)
elseif(UNIX AND NOT APPLE)
    target_compile_definitions(IdealCache PRIVATE IS_LINUX)
elseif(APPLE)
    target_compile_definitions(IdealCache PRIVATE IS_MACOS)
endif()

if(WIN32)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()
