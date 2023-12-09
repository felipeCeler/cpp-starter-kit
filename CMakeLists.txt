# CMake version
# Template based on cmake-init project @see https://github.com/cginternals/cmake-init
cmake_minimum_required(VERSION 3.15...3.17 FATAL_ERROR)

# Maybe stop from "CMaKeing" in the wrong place
if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Source and build directories cannot be the same. Use the /build directory.")
endif()

#
# Configure CMake environment
#

# Include cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# 
# Project description and (meta) information
# 

# Meta information about the project
set(META_PROJECT_NAME        "sample-project")
#set(META_API_NAME            "SAMPLE-PROJECT_API_EXPORT")
set(META_PROJECT_DESCRIPTION "Sample Project Start Kit")
set(META_AUTHOR_ORGANIZATION "Hops System")
set(META_AUTHOR_DOMAIN       "https://www.myself.me")
set(META_AUTHOR_MAINTAINER   "me@myself.me")
set(META_VERSION_MAJOR       "1")
set(META_VERSION_MINOR       "0")
set(META_VERSION_PATCH       "0")
set(META_VERSION             "${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_VERSION_PATCH}")
set(META_NAME_VERSION        "${META_PROJECT_NAME} v${META_VERSION} (${META_VERSION_REVISION})")

# 
# Declare project
# 

# Generate folders for IDE targets (e.g., VisualStudio solutions)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(IDE_FOLDER ${META_PROJECT_NAME})

project(${META_PROJECT_NAME} 
        VERSION ${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_VERSION_PATCH}
        DESCRIPTION ${META_PROJECT_DESCRIPTION}
        LANGUAGES C CXX 
        )

# 
# Project configuration options
# 

# Project options
option(BUILD_SHARED_LIBS        "Build shared instead of static libraries."              ON)
option(OPTION_BUILD_DOCS        "Build documentation."                                   OFF)
option(OPTION_BUILD_EXAMPLES    "Build examples."                                        ON)

option(OPTION_BUILD_GLFW        "Build GLFW."                                       OFF)
option(OPTION_BUILD_Qt5         "Build Qt5."                                        OFF)
option(OPTION_BUILD_Qt6         "Build QT6."                                        ON)


# Rename project folder into META_PROJECT_NAME
file(GLOB project_name RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*)

if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/${META_PROJECT_NAME})
        file(RENAME ${CMAKE_CURRENT_SOURCE_DIR}/${project_name} ${CMAKE_CURRENT_SOURCE_DIR}/src/${META_PROJECT_NAME})
endif()

# Build third party libraries
include(libs/third_party.cmake)

## - Examples using and Qt5
add_subdirectory(src/${META_PROJECT_NAME})

