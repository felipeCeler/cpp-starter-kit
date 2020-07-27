# Target name
set(target sample-project)

set(CMAKE_BUILD_TYPE "DEBUG")

message(STATUS "Lib ${target} as ${CMAKE_BUILD_TYPE}")

find_package(Qt5 COMPONENTS Widgets Gui REQUIRED)
#find_package(glad REQUIRED NO_MODULE)
#find_package(glm REQUIRED NO_MODULE)


# Enable automoc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(AUTOMOC_MOC_OPTIONS PROPERTIES FOLDER CMakeAutomocTargets)
set_property(GLOBAL PROPERTY AUTOMOC_FOLDER CMakeAutomocTargets)

# ENABLE CMP0020: Automatically link Qt executables to qtmain target on Windows.
cmake_policy(SET CMP0020 NEW)


# Target name

# Exit here if required dependencies are not met
if (NOT Qt5Core_FOUND)
    message(STATUS "Example ${target} skipped: Qt5 not found")
    return()
endif()

# Build Executable
add_executable(${target})

# 
# Sources
#

target_sources( ${target}      
    PRIVATE
      gui/qt5/about_widget/about_widget.hpp
      gui/qt5/about_widget/about_widget.cpp
      gui/qt5/about_widget/about_widget_form.ui
      gui/qt5/opengl_canvas_widget/opengl_canvas_widget.hpp
      gui/qt5/opengl_canvas_widget/opengl_canvas_widget.cpp
      gui/qt5/main_window/main_window.hpp
      gui/qt5/main_window/main_window.cpp
      gui/qt5/main_window/main_window_form.ui
      main.cpp
)

# Create namespaced alias
add_executable(${META_PROJECT_NAME}::${target} ALIAS ${target})

# 
# Project options
# 

set ( OUTPUT  "${CMAKE_BINARY_DIR}/build/${target}")

set_target_properties(${target}
    PROPERTIES
      # cmake/CompileOptions.cmake
      ${DEFAULT_PROJECT_OPTIONS}
      # Targets with no FOLDER property will appear as top level entities in IDEs like Visual Studio
      FOLDER ${target}
      # Example: extension .exe
      OUTPUT_NAME ${target} 
      SUFFIX ".bin"
      PREFIX "qt5-"
      CXX_STANDARD 17
        
    ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT}/data"
    LIBRARY_OUTPUT_DIRECTORY "${OUTPUT}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${OUTPUT}/bin"
)

# 
# Include directories
# 

target_include_directories(${target}
    PRIVATE
      ${DEFAULT_INCLUDE_DIRECTORIES}
    SYSTEM
      ${CMAKE_CURRENT_SOURCE_DIR}    
)

# 
# Libraries
# 

target_link_libraries(${target}
    PRIVATE             
        Qt5::Gui
        Qt5::Widgets  
        glm::glm
        dl
        glad
)



# 
# Compile definitions
# 

target_compile_definitions(${target}
    PRIVATE
        ${DEFAULT_COMPILE_DEFINITIONS}
        #@see https://github.com/cginternals/glbinding/blob/16d5d987bd65a6278066b3601b695b811fe943df/source/examples/comparison/CMakeLists.txt
)


# 
# Compile options
# 

# As an alternative, CMake also offers a finer grained approach, allowing you to specify the compiler features
# @see https://crascit.com/2015/03/28/enabling-cxx11-in-cmake/

target_compile_options(${target}
    PRIVATE
        ${DEFAULT_COMPILE_OPTIONS}
)


# 
# Linker options
# 

target_link_libraries(${target}
    PRIVATE
      ${DEFAULT_LINKER_OPTIONS}
)


set (assets_source "${CMAKE_CURRENT_SOURCE_DIR}/gui/qt5/assets")
             
set (assets_destination "${OUTPUT}/bin/assets")

add_custom_target(${target}_assets ALL
                   DEPENDS ${assets_source}
                   COMMENT "Copying Asserts: ${assets_source} ${DESTINATION}" )
                 
add_custom_command(
                TARGET ${target}_assets
                COMMAND ${CMAKE_COMMAND} -E copy_directory ${assets_source} ${assets_destination} )   
         


