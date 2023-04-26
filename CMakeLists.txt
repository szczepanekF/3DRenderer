cmake_minimum_required(VERSION 3.22.1)
project(Chess)

enable_testing()
set(CMAKE_CXX_STANDARD 23)

set(CONAN_SYSTEM_INCLUDES ON)
include(${CMAKE_SOURCE_DIR}/cmake/CMakeFunctions.cmake)
setup_conan()
add_subdirectory(src)
add_subdirectory(tests)





