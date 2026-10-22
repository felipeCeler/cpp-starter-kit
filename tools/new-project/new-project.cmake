# ==============================================================================
# CMake Project Skeleton Generator (CMake 4.0+ Script Mode)
#
# Usage:
#   cmake -DNAME="my-project" -DOUT="../my-project" -P tools/new-project/new-project.cmake
# ==============================================================================

cmake_minimum_required(VERSION 4.0.0)

if(NOT DEFINED NAME OR "${NAME}" STREQUAL "")
    message(FATAL_ERROR "Usage: cmake -DNAME=<project-name> [-DOUT=<output-dir>] -P tools/new-project/new-project.cmake")
endif()

# Validate project name (alphanumeric, '-', '_')
if(NOT "${NAME}" MATCHES "^[A-Za-z0-9_-]+$")
    message(FATAL_ERROR "Invalid project name '${NAME}'. Use only letters, digits, '-' or '_'.")
endif()

# Resolve repository root (two levels up from tools/new-project/)
get_filename_component(REPO_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)

if(NOT DEFINED OUT OR "${OUT}" STREQUAL "")
    get_filename_component(PARENT_DIR "${REPO_ROOT}/.." ABSOLUTE)
    set(DEST_DIR "${PARENT_DIR}/${NAME}")
else()
    get_filename_component(DEST_DIR "${OUT}" ABSOLUTE)
endif()

if(EXISTS "${DEST_DIR}")
    message(FATAL_ERROR "Destination directory already exists: ${DEST_DIR}")
endif()

message(STATUS "Creating new project '${NAME}' at '${DEST_DIR}'...")
file(MAKE_DIRECTORY "${DEST_DIR}")

# 1. Copy top-level files and directories
set(ITEMS_TO_COPY
    ".gitignore"
    "CMakeLists.txt"
    "CMakePresets.json"
    "CMakeUserPresets.json.example.md"
    "README.md"
    "cmake"
    "libs"
    "src"
)

foreach(item IN LISTS ITEMS_TO_COPY)
    if(EXISTS "${REPO_ROOT}/${item}")
        file(COPY "${REPO_ROOT}/${item}" DESTINATION "${DEST_DIR}")
    endif()
endforeach()

# 2. Rename src/sample-project -> src/${NAME}
set(OLD_SRC_DIR "${DEST_DIR}/src/sample-project")
set(NEW_SRC_DIR "${DEST_DIR}/src/${NAME}")

if(EXISTS "${OLD_SRC_DIR}" AND NOT "${NAME}" STREQUAL "sample-project")
    file(RENAME "${OLD_SRC_DIR}" "${NEW_SRC_DIR}")
endif()

# 3. Clean generated *-config.cmake files and rename *-config.cmake.in templates
file(GLOB_RECURSE GENERATED_CMAKE_CONFIGS
    "${NEW_SRC_DIR}/*-config.cmake"
    "${NEW_SRC_DIR}/*-config-version.cmake"
)
if(GENERATED_CMAKE_CONFIGS)
    file(REMOVE ${GENERATED_CMAKE_CONFIGS})
endif()

file(GLOB_RECURSE TEMPLATE_CMAKE_CONFIGS "${NEW_SRC_DIR}/*sample-project*-config.cmake.in")
foreach(tpl_path IN LISTS TEMPLATE_CMAKE_CONFIGS)
    get_filename_component(tpl_dir "${tpl_path}" DIRECTORY)
    get_filename_component(tpl_name "${tpl_path}" NAME)
    string(REPLACE "sample-project" "${NAME}" new_tpl_name "${tpl_name}")
    if(NOT "${tpl_name}" STREQUAL "${new_tpl_name}")
        file(RENAME "${tpl_path}" "${tpl_dir}/${new_tpl_name}")
    endif()
endforeach()

# 4. Update META_PROJECT_NAME in root CMakeLists.txt
set(ROOT_CMAKELISTS "${DEST_DIR}/CMakeLists.txt")
file(READ "${ROOT_CMAKELISTS}" CMAKELISTS_CONTENT)
string(REPLACE
    "set(META_PROJECT_NAME \"sample-project\")"
    "set(META_PROJECT_NAME \"${NAME}\")"
    CMAKELISTS_CONTENT
    "${CMAKELISTS_CONTENT}"
)
file(WRITE "${ROOT_CMAKELISTS}" "${CMAKELISTS_CONTENT}")

# 5. Initialize a fresh git repository
find_program(GIT_EXECUTABLE git)
if(GIT_EXECUTABLE)
    execute_process(
        COMMAND "${GIT_EXECUTABLE}" init -q
        WORKING_DIRECTORY "${DEST_DIR}"
        RESULT_VARIABLE GIT_RESULT
    )
    if(GIT_RESULT EQUAL 0)
        message(STATUS "Initialized empty Git repository in '${DEST_DIR}'")
    endif()
endif()

message(STATUS "Done! Next steps:")
message(STATUS "  cd ${DEST_DIR}")
message(STATUS "  cp CMakeUserPresets.json.example.md CMakeUserPresets.json # or configure your local preset")

