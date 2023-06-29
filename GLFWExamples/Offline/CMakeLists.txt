cmake_minimum_required(VERSION 3.20)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
   set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()
# our project name
project(GLFWOfflineExample)
# Now find the SDL2  and OpenGL librarys
find_package(glfw3 CONFIG REQUIRED)
find_package(gl3w CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

# Set to C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
# silence the OpenGL deprecated warnings on mac
add_definitions(-DGL_SILENCE_DEPRECATION)
add_executable(GLFWOffline)
target_sources(GLFWOffline PRIVATE main.cpp )
target_link_libraries(GLFWOffline PRIVATE  glfw unofficial::gl3w::gl3w OpenGL::GL)

