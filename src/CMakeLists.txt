cmake_minimum_required(VERSION 3.25)

project(src)
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib
)
add_executable(3DRenderer main.cpp)


