cmake_minimum_required(VERSION 2.8)
project(uploadAndRetrieve)

# Locate the AWS SDK for C++ package.
# Requires that you build with:
# -Daws-sdk-cpp_DIR=/path/to/sdk_build
# or export/set:
# CMAKE_PREFIX_PATH=/path/to/sdk_build
# CMAKE_PREFIX_PATH=/Users/zeph/cpp/aws-sdk-cpp

#this will locate the aws sdk for c++ package so that we can use its targets
find_package(aws-sdk-cpp)

#set(AWS_CPP_SDK_INCLUDE_DIRS /Users/zeph/cpp/aws-sdk-cpp CACHE STRING "aws-cpp-sdk include directories")
#set(AWS_CPP_SDK_CORE_LIB "-l:/path/to/libaws-cpp-sdk-core.so" CACHE STRING "aws-cpp-sdk link core lib")
#set(AWS_CPP_SDK_S3_LIB "-l:/path/to/libaws-cpp-sdk-s3.so" CACHE STRING "aws-cpp-sdk link S3 lib")

add_definitions(-DUSE_IMPORT_EXPORT)

add_executable(uploadAndRetrieve uploadAndRetrieve.cpp)

#since we called find_package(), this will resolve all dependencies, header files, and cflags necessary
#to build and link your executable. 
target_link_libraries(uploadAndRetrieve aws-cpp-sdk-s3)
