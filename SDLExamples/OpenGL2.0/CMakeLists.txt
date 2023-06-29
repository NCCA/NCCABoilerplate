cmake_minimum_required(VERSION 3.20)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
   set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()
# our project name
project(SDLOpenGL2Example)
# Now find the SDL2  and OpenGL librarys
find_package(SDL2 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLM CONFIG REQUIRED)

# Set to C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
# silence the OpenGL deprecated warnings on mac
add_definitions(-DGL_SILENCE_DEPRECATION)
add_executable(SDLOpenGL2)
target_sources(SDLOpenGL2 PRIVATE main.cpp )
target_link_libraries(SDLOpenGL2 PRIVATE  SDL2::SDL2 SDL2::SDL2main OpenGL::GL glm::glm)

