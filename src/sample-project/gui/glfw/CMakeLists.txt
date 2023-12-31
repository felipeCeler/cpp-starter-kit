# 
# Library name and options
# 

# Target name
set(target ${META_PROJECT_NAME}-glfw)

# Exit here if required dependencies are not met
message(STATUS "Lib ${target} as ${CMAKE_BUILD_TYPE}")

file(GLOB old_cmake_files ${CMAKE_CURRENT_SOURCE_DIR}/cmake/*.cmake)
if (old_cmake_files)
    file (REMOVE ${old_cmake_files})
endif()

file(GLOB cmake_in_name RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} cmake/*config.cmake.in)
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${target}-config.cmake.in)
        file(RENAME ${CMAKE_CURRENT_SOURCE_DIR}/${cmake_in_name} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${target}-config.cmake.in)
endif()


# 
# Sources
# 

# find_package HINTS
# for linux it will search on the given directory (named prefix) for:
#   <prefix>/                                               (W)
#   <prefix>/(cmake|CMake)/                                 (W)
#   <prefix>/<name>*/                                       (W)
#   <prefix>/<name>*/(cmake|CMake)/                         (W)
#   <prefix>/(lib/<arch>|lib|share)/cmake/<name>*/          (U)
#   <prefix>/(lib/<arch>|lib|share)/<name>*/                (U)
#   <prefix>/(lib/<arch>|lib|share)/<name>*/(cmake|CMake)/  (U)

# @see https://stackoverflow.com/questions/55820716/how-to-predict-cmakes-choice-of-libdir-on-a-given-platform
# @see https://cmake.org/cmake/help/v3.0/command/find_package.html

find_package(glad REQUIRED PATHS "${THIRD_PARTY_INSTALL_DIR}/glad" NO_DEFAULT_PATH)
find_package(glm REQUIRED PATHS "${THIRD_PARTY_INSTALL_DIR}/glm" NO_DEFAULT_PATH)
find_package(glfw3 REQUIRED PATHS "${THIRD_PARTY_INSTALL_DIR}/glfw" NO_DEFAULT_PATH)

# 
# Create library
# 

# @ see https://hsf-training.github.io/hsf-training-cmake-webpage/aio/index.html
#   target_link_libraries: Other targets; can also pass library names directly
#   target_include_directories: Include directories
#   target_compile_features: The compiler features you need activated, like cxx_std_11
#   target_compile_definitions: Definitions
#   target_compile_options: More general compile flags
#   target_link_directories: Don’t use, give full paths instead (CMake 3.13+)
#   target_link_options: General link flags (CMake 3.13+)
#   target_sources: Add source files

# Build library
add_executable(${target})

# Create namespaced alias
add_executable(${META_PROJECT_NAME}::${target} ALIAS ${target})

# Set target sources
# Issue when install using target_source 
# For while, everything will be set PRIVATE
#    @see https://stackoverflow.com/questions/60736689/cmake-target-sources-and-install
#    @see https://stackoverflow.com/questions/62348945/cmake-error-target-foo-interface-sources-property-contains-path-which-is-prefi
#    @see https://cmake.org/pipermail/cmake/2016-July/063907.html
target_sources( ${target}      
    PRIVATE
      main.cpp
)

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
      SUFFIX ".exe"
      PREFIX "glfw3-"
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
        ${CMAKE_CURRENT_SOURCE_DIR}        
    PUBLIC        
)


# 
# Libraries
# 

target_link_libraries(${target}
    PRIVATE
        
    PUBLIC
        # Modern OpenGL Extension Loader    
        glad::glad
        glm::glm
        glfw
        # On Linux we need libdl.so
        $<$<BOOL:${UNIX}>:dl>
    INTERFACE
)


# 
# Compile definitions
# 

target_compile_definitions(${target}
    PRIVATE
    
    PUBLIC    
        
    INTERFACE
)

target_compile_features(${target} 
    PRIVATE
    
    PUBLIC    
    
    INTERFACE
)

# 
# Compile options
# 

target_compile_options(${target}
    PRIVATE
        # possible ID for Compiler @see https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html        
    PUBLIC

    INTERFACE
)


# 
# Linker options
# 

target_link_libraries(${target}
    PRIVATE

    PUBLIC
        
    INTERFACE
)


# 
# Deployment
# 

# Need a better documentation

## Header files
include(GNUInstallDirs)
include(InstallRequiredSystemLibraries)

install(TARGETS ${target} 
    EXPORT 
        ${target}-targets
    ARCHIVE 
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT Runtime
    RUNTIME 
        DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT Runtime
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${target}-config.cmake.in
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${target}-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${target}
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${target}-config-version.cmake
    VERSION ${${target}_VERSION}
    COMPATIBILITY AnyNewerVersion
)

