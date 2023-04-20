cmake_minimum_required(VERSION 3.22.1)

project(src)
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib
)

add_executable(3DRenderer ../main.cpp)
find_package(OpenGL REQUIRED)
include_directories(${glfw3_INCLUDE_DIRS})
target_link_libraries(3DRenderer Opengl:GL ${CONAN_LIBS}  ${glfw3_LIBRARIES})

