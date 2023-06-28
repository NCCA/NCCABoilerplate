cmake_minimum_required(VERSION 3.20)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
   set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()

project(GTestExample)

# Set to C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# find the gtest package
find_package(GTest CONFIG REQUIRED)
# this will find all the gtest functios
include(GoogleTest)

enable_testing()

add_executable(GTestBoilerPlate)
target_sources(GTestBoilerPlate PRIVATE main.cpp)
target_link_libraries(GTestBoilerPlate PRIVATE GTest::gtest GTest::gtest_main )

gtest_discover_tests(GTestBoilerPlate)
