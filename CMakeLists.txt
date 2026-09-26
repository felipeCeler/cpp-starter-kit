# CMake version
# Template based on cmake-init project @see https://github.com/cginternals/cmake-init
cmake_minimum_required(VERSION 4.0 FATAL_ERROR)

# Maybe stop from "CMaKeing" in the wrong place
if(CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
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
# Change the src/sample-project to the name of your project, and the META_PROJECT_NAME to the same name as well.
set(META_PROJECT_NAME "sample-project")

string(TOUPPER "${META_PROJECT_NAME}" META_PROJECT_NAME_UPPER)
# 2. Concatenate the uppercase name with the "_API_EXPORT" suffix
string(CONCAT EXPORT_MACRO_NAME "${META_PROJECT_NAME_UPPER}" "_API_EXPORT")

set(META_API_NAME            ${EXPORT_MACRO_NAME})
set(META_PROJECT_DESCRIPTION "Sample Project Start Kit")
set(META_AUTHOR_ORGANIZATION "Hops System")
set(META_AUTHOR_DOMAIN "https://www.myself.me")
set(META_AUTHOR_MAINTAINER "me@myself.me")
set(META_VERSION_MAJOR "1")
set(META_VERSION_MINOR "0")
set(META_VERSION_PATCH "0")
set(META_VERSION "${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_VERSION_PATCH}")
set(META_NAME_VERSION "${META_PROJECT_NAME} v${META_VERSION} (${META_VERSION_REVISION})")

#
# Declare project
#

# Generate folders for IDE targets (e.g., VisualStudio solutions)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(${META_PROJECT_NAME}
        VERSION ${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_VERSION_PATCH}
        DESCRIPTION ${META_PROJECT_DESCRIPTION}
        LANGUAGES C CXX
)

#
# Project configuration options
#

# Project options
option(BUILD_SHARED_LIBS "Build shared instead of static libraries." ON)
option(OPTION_BUILD_DOCS "Build documentation."                      OFF)
option(OPTION_BUILD_EXAMPLES "Build examples."                       ON)

option(OPTION_BUILD_GLFW "Build GLFW."                               OFF)
option(OPTION_BUILD_Qt6  "Build  QT6."                                ON)

# Build third party libraries
include(libs/third_party.cmake)

add_subdirectory(src/${META_PROJECT_NAME})
