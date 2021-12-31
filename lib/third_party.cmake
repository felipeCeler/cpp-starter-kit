# From the Gist @see https://gist.github.com/amir-saniyan/4339e6f3ef109c75eda8018f7d5192a7

function (build_external_project target file_name)

    set(CMAKELIST_CONTENT "
        cmake_minimum_required(VERSION ${CMAKE_MINIMUM_REQUIRED_VERSION})
        project(build_external_project)
        file(MD5 \"${file_name}\" FILE_HASH)
        include(ExternalProject)
        ExternalProject_add(${target}
            URL \"${file_name}\"
            URL_MD5 \${FILE_HASH}
            CMAKE_GENERATOR \"${CMAKE_GENERATOR}\"
            CMAKE_GENERATOR_PLATFORM \"${CMAKE_GENERATOR_PLATFORM}\"
            CMAKE_GENERATOR_TOOLSET \"${CMAKE_GENERATOR_TOOLSET}\"
            CMAKE_GENERATOR_INSTANCE \"${CMAKE_GENERATOR_INSTANCE}\"
            CMAKE_ARGS ${ARGN})
        add_custom_target(build_external_project)
        add_dependencies(build_external_project ${target})
    ")

    set(TARGET_DIR "${CMAKE_CURRENT_BINARY_DIR}/ExternalProjects/${target}")

    file(WRITE "${TARGET_DIR}/CMakeLists.txt" "${CMAKELIST_CONTENT}")

    file(MAKE_DIRECTORY "${TARGET_DIR}" "${TARGET_DIR}/build")

    execute_process(COMMAND ${CMAKE_COMMAND}
        -G "${CMAKE_GENERATOR}"
        -A "${CMAKE_GENERATOR_PLATFORM}"
        -T "${CMAKE_GENERATOR_TOOLSET}"
        ..
        WORKING_DIRECTORY "${TARGET_DIR}/build")

    execute_process(COMMAND ${CMAKE_COMMAND}
        --build .
        --config ${CMAKE_BUILD_TYPE}
        WORKING_DIRECTORY "${TARGET_DIR}/build")

endfunction(build_external_project)

#----------------------------------------------------------------------------------------------------

set(THIRD_PARTY_DIR "${CMAKE_CURRENT_LIST_DIR}")
message("CMAKE_CURRENT_LIST_DIR " ${CMAKE_CURRENT_LIST_DIR})
set(THIRD_PARTY_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/third_party")

#----------------------------------------------------------------------------------------------------

# glad.
set( current_lib "glad")
set( current_source "glad-0.1.36.zip")
set(GLAD_OPTIONS "-DGLAD_INSTALL=ON"
                 "-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}"
                 "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
                 "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
                 "-DCMAKE_POSITION_INDEPENDENT_CODE=ON"
                 "-DBUILD_SHARED_LIBS=OFF"
                 "-DCMAKE_INSTALL_PREFIX=${THIRD_PARTY_INSTALL_DIR}/${current_lib}")

build_external_project(${current_lib} "${THIRD_PARTY_DIR}/${current_lib}/${current_source}" ${GLAD_OPTIONS})

# glm.
set( current_lib "glm")
set( current_source "glm-6ad79aae3eb5bf809c30bf1168171e9e55857e45.zip")
set(GLM_OPTIONS "-DBUILD_TESTING=OFF"
                "-DBUILD_SHARED_LIBS=OFF"
                "-DBUILD_STATIC_LIBS=ON"
                "-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}"
                "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
                "-DCMAKE_POSITION_INDEPENDENT_CODE=ON"
                "-DCMAKE_INSTALL_PREFIX=${THIRD_PARTY_INSTALL_DIR}/${current_lib}")

build_external_project(${current_lib} "${THIRD_PARTY_DIR}/${current_lib}/${current_source}" ${GLM_OPTIONS})

# tinyobjloader.
set( current_lib "tinyobjloader")
set( current_source "tinyobjloader-2.0.0rc7.zip")
set(TINYOBJLOADER_OPTIONS "-DBUILD_STATIC_LIBS=ON"
                          "-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}"
                          "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
                          "-DCMAKE_POSITION_INDEPENDENT_CODE=ON"
                          "-DCMAKE_INSTALL_PREFIX=${THIRD_PARTY_INSTALL_DIR}/${current_lib}")

build_external_project(${current_lib} "${THIRD_PARTY_DIR}/${current_lib}/${current_source}" ${TINYOBJLOADER_OPTIONS})

#----------------------------------------------------------------------------------------------------

####################################################################################################
# Now, you can use find_package:
#find_package(OpenCV REQUIRED PATHS "${THIRD_PARTY_INSTALL_DIR}/glad" NO_DEFAULT_PATH)
#find_package(dlib REQUIRED PATHS "${THIRD_PARTY_INSTALL_DIR}/glm" NO_DEFAULT_PATH)
####################################################################################################

