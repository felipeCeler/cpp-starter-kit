# CMake version
# Template based on cmake-init project @see https://github.com/cginternals/cmake-init
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

#
# Configure CMake environment
#

# Include cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_INIT_PATH}/cmake")

# 
# Project description and (meta) information
# 

# Meta information about the project
set(META_PROJECT_NAME        "default-qt5")
set(META_PROJECT_DESCRIPTION "Qt5 OpenGL Project Template")
set(META_AUTHOR_ORGANIZATION "Celer System")
set(META_AUTHOR_DOMAIN       "https://www.felipedecarvalho.com")
set(META_AUTHOR_MAINTAINER   "felipe.celer@gmail.com")
set(META_VERSION_MAJOR       "1")
set(META_VERSION_MINOR       "0")
set(META_VERSION_PATCH       "0")

# Set the desired project name
project( ${META_PROJECT_NAME} VERSION 0.1
           DESCRIPTION "Qt5 OpenGL starter kit"
           LANGUAGES C CXX 
        )

# 
# Project configuration options
# 

# Project options
option(BUILD_SHARED_LIBS      "Build shared instead of static libraries."              OFF)
option(OPTION_BUILD_DOCS      "Build documentation."                                   OFF)
option(OPTION_BUILD_EXAMPLES  "Build examples."                                        OFF)

# 
# Declare project
# 

# Generate folders for IDE targets (e.g., VisualStudio solutions)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(IDE_FOLDER ${PROJECT_NAME})

# Declare project
project(${META_PROJECT_NAME} C CXX)


# 
# Project Dependecies
# 

set(glad_DIR          "${CMAKE_SOURCE_DIR}/libs/glad/install/lib/cmake/glad")
set(glm_DIR           "${CMAKE_SOURCE_DIR}/libs/glm/src/cmake/glm") 

## - Examples using and Qt5
add_subdirectory(src/sample_project)



