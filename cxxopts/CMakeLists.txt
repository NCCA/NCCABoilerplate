cmake_minimum_required(VERSION 3.20)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
   set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()
# our project name
project(CXXOPTExample)
# Now find the fmt and glm librarys
find_package(cxxopts CONFIG REQUIRED)

# Set to C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_executable(CXXOPTBoilerPlate)
target_sources(CXXOPTBoilerPlate PRIVATE main.cpp )
target_link_libraries(CXXOPTBoilerPlate PRIVATE cxxopts::cxxopts)

