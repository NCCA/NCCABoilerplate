cmake_minimum_required(VERSION 3.20)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
   set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()

project(GTestExmaple)
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

enable_testing()

add_executable(GTestBoilerPlate main.cpp )
target_link_libraries(GTestBoilerPlate PRIVATE GTest::gtest GTest::gtest_main )

gtest_discover_tests(GTestBoilerPlate)
