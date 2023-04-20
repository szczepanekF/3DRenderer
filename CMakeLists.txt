cmake_minimum_required(VERSION 3.22.1)
project(3DRenderer)
set(CMAKE_CXX_STANDARD 23)




if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
            TLS_VERIFY ON)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

include(${CMAKE_BINARY_DIR}/conan.cmake)



conan_cmake_configure(REQUIRES glfw/3.3.8
        GENERATORS CMakeDeps CMakeToolchain)

conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE .
        BUILD missing
        REMOTE conancenter
        SETTINGS ${settings})

#add_subdirectory(lib)
#add_subdirectory(src)
#find_package(glfw/3.3.8)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
add_executable(3DRenderer main.cpp)
target_link_libraries(3DRenderer glfw)
target_link_libraries(3DRenderer OpenGL)