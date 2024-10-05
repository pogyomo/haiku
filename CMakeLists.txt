cmake_minimum_required(VERSION 3.5)
project(haiku CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FlAGS "${CMAKE_C_FLAGS} -Wall -O3")
set(CMAKE_CXX_FlAGS "${CMAKE_CXX_FLAGS} -Wall -O3")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(PROJECT_NAME src/main.cc)
target_include_directories(PROJECT_NAME PRIVATE include)

find_package(Eigen3 REQUIRED NO_MODULE)
target_link_libraries(PROJECT_NAME Eigen3::Eigen)
