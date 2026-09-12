cmake_minimum_required(VERSION 3.20)
project(CompilerTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(raylib REQUIRED)

set(SOURCES
    main.c
)

add_executable(CompilerTest ${SOURCES})

target_link_libraries(CompilerTest PRIVATE raylib)