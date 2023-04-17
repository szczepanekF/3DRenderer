cmake_minimum_required(VERSION 3.25)
project(Lib)

set(SOURCE_FILES Ray.h ../src/Ray.cpp)


add_library(Lib ${SOURCE_FILES})