cmake_minimum_required(VERSION 3.1)
project(game)

set(CMAKE_CXX_STANDARD 14)
find_package(Curses REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory("project")
