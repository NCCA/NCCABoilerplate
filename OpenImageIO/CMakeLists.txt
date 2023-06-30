cmake_minimum_required(VERSION 3.20)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
   set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()

project(OpenImageIOExample)

# Set to C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# find the gtest package
find_package(OpenImageIO CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)
set(Boost_NO_WARN_NEW_VERSIONS 1)
find_package(Boost COMPONENTS filesystem thread)


enable_testing()

add_executable(OpenImageIOExample)
target_sources(OpenImageIOExample PRIVATE main.cpp)
target_link_libraries(OpenImageIOExample PRIVATE Catch2::Catch2 OpenImageIO::OpenImageIO  Boost::filesystem Boost::thread)

gtest_discover_tests(OpenImageIOExample)
