# Origin: https://github.com/xdbr/cmake-module-submodule.cmake/blob/master/submodules.cmake
if(EXISTS "${PROJECT_SOURCE_DIR}/.gitmodules")
message(STATUS "Updating submodules...")

if(${GIT_SUBMODULES_QUIET})
    execute_process(
        COMMAND             git submodule update --init --recursive
        WORKING_DIRECTORY   ${PROJECT_SOURCE_DIR}
        OUTPUT_QUIET
        ERROR_QUIET
    )
else()
    execute_process(
        COMMAND             git submodule update --init --recursive
        WORKING_DIRECTORY   ${PROJECT_SOURCE_DIR}
    )
endif()

endif()
