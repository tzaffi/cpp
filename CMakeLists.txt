cmake_minimum_required(VERSION 3.5)
project(cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES)

add_executable(basicTypes ${SOURCE_FILES} DMCpp/basicTypes.cpp)

add_executable(age ${SOURCE_FILES} DMCpp/1_10_1_age.cpp)

add_executable(arraysAndPointers ${SOURCE_FILES} DMCpp/1_10_2_ArraysAndPointers.cpp)

add_executable(NonOOquickSort sorting/NonOOquickSort.cpp)