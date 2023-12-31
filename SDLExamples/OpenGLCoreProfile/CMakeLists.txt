cmake_minimum_required(VERSION 3.20)
#-------------------------------------------------------------------------------------------
# I'm going to use vcpk in most cases for our install of 3rd party libs
# this is going to check the environment variable for CMAKE_TOOLCHAIN_FILE and this must point to where
# vcpkg.cmake is in the University this is set in your .bash_profile to
# export CMAKE_TOOLCHAIN_FILE=/public/devel/2020/vcpkg/scripts/buildsystems/vcpkg.cmake
#-------------------------------------------------------------------------------------------
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
   set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()

# Name of the project
project(SDL2TriangleGLEWBuild)
# This is the name of the Exe change this and it will change everywhere
set(TargetName SDL2TriangleGLEW)
# find Qt libs
find_package(SDL2 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
if(${CMAKE_SYSTEM_NAME}  MATCHES "Linux" OR ${CMAKE_SYSTEM_NAME}  MATCHES  "Windows")
	find_package(GLEW REQUIRED)
endif()
	# use C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
# Set the name of the executable we want to build
add_executable(${TargetName})
include_directories(include)
# Add NGL include path
target_sources(${TargetName} PRIVATE 
${PROJECT_SOURCE_DIR}/src/main.cpp  
${PROJECT_SOURCE_DIR}/src/GLFunctions.cpp 
${PROJECT_SOURCE_DIR}/include/GLFunctions.h  
)

# see what platform we are on and set platform defines
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	add_definitions(-DGL_SILENCE_DEPRECATION)
endif()


# add exe and link libs that must be after the other defines
target_link_libraries(${TargetName} PRIVATE  SDL2::SDL2 SDL2::SDL2main OpenGL::GL glm::glm)

if(${CMAKE_SYSTEM_NAME}  MATCHES "Linux" OR ${CMAKE_SYSTEM_NAME}  MATCHES  "Windows")
	target_link_libraries(${TargetName} PRIVATE  GLEW::GLEW)
endif()