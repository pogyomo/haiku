cmake_minimum_required(VERSION 3.5)
project(haiku CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Require c++17 but reject compiler extensions
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src)
