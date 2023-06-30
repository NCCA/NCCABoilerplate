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
project(NCCABoilerPlateAll)
# for each subdirectory add the CMakeLists.txt file
add_subdirectory(${PROJECT_SOURCE_DIR}/Bullet)
add_subdirectory(${PROJECT_SOURCE_DIR}/Eigen)
add_subdirectory(${PROJECT_SOURCE_DIR}/glm)
add_subdirectory(${PROJECT_SOURCE_DIR}/GTest)
add_subdirectory(${PROJECT_SOURCE_DIR}/fmt)
add_subdirectory(${PROJECT_SOURCE_DIR}/OpenImageIO)
add_subdirectory(${PROJECT_SOURCE_DIR}/SDLExamples)
add_subdirectory(${PROJECT_SOURCE_DIR}/TBB)

add_subdirectory(${PROJECT_SOURCE_DIR}/GLFWExamples)

# These projects are excluded from the github actions
# as they need extra software to be installed
if  (NOT ON_CI)
  add_subdirectory(${PROJECT_SOURCE_DIR}/MayaAPI)
endif()