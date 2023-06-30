cmake_minimum_required(VERSION 3.20)
project(CustomSphere)

if (NOT DEFINED ENV{DEVKIT_LOCATION})
    message(WARNING "Please set DEVKIT_LOCATION to your Maya devkit location")
    message(WARNING "See README.md for more information")
else()
    # include the project setting file
    include($ENV{DEVKIT_LOCATION}/cmake/pluginEntry.cmake)
    # set SOURCE_FILES
    set(SOURCE_FILES   src/CustomSphere.cpp src/Plugin.cpp include/CustomSphere.h )
    include_directories(include)
    # set linking libraries
    set(LIBRARIES OpenMaya Foundation)
    # Build plugin
    build_plugin()
endif()