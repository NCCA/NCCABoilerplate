cmake_minimum_required(VERSION 3.20)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
   set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()
# our project name
project(GLFWOpenGL2.0Example)
# Now find the glfw3  and OpenGL librarys
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL  REQUIRED)
find_package(glm CONFIG REQUIRED)

# Set to C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
# silence the OpenGL deprecated warnings on mac
add_definitions(-DGL_SILENCE_DEPRECATION)
add_executable(GLFWOpenGL2.0)
target_sources(GLFWOpenGL2.0 PRIVATE main.cpp )
target_link_libraries(GLFWOpenGL2.0 PRIVATE  glfw glm::glm OpenGL::GL)

