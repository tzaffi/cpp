cmake_minimum_required(VERSION 3.5)
project(cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES helpers/Printer.h helpers/Printer.cpp helpers/coutFriends.h helpers/coutFriends.cpp)

add_executable(basicTypes ${SOURCE_FILES} DMCpp/basicTypes.cpp)

add_executable(age ${SOURCE_FILES} DMCpp/1_10_1_age.cpp)

add_executable(arraysAndPointers ${SOURCE_FILES} DMCpp/1_10_2_ArraysAndPointers.cpp)

add_executable(NonOOquickSort sorting/NonOOquickSort.cpp)

add_executable(TwoSum leetcode/TwoSum.cpp ${SOURCE_FILES})

add_executable(ThreeSum leetcode/ThreeSum.cpp ${SOURCE_FILES})

add_executable(IsCompleteCycle GTraining/IsCompleteCycle.cpp ${SOURCE_FILES})
