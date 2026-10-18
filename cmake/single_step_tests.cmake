function(resolve_single_step_tests_dir)
    set(SINGLE_STEP_TESTS_DIR "" CACHE PATH "Path to the SingleStepTests JSON files")
    if(NOT SINGLE_STEP_TESTS_DIR)
        find_path(SINGLE_STEP_TESTS_DIR_DEFAULT
            NAMES 00.json
            PATHS "${PROJECT_SOURCE_DIR}/tests/single_step_tests/v1"
            NO_DEFAULT_PATH
        )
        if(NOT SINGLE_STEP_TESTS_DIR_DEFAULT)
            message(FATAL_ERROR "Could not find SingleStepTests JSON files in tests/single_step_tests/v1")
        endif()
        set(SINGLE_STEP_TESTS_DIR "${SINGLE_STEP_TESTS_DIR_DEFAULT}")
    endif()

    if(NOT IS_DIRECTORY "${SINGLE_STEP_TESTS_DIR}")
        message(FATAL_ERROR "SINGLE_STEP_TESTS_DIR is not a directory: ${SINGLE_STEP_TESTS_DIR}")
    endif()

    get_filename_component(SINGLE_STEP_TESTS_DIR "${SINGLE_STEP_TESTS_DIR}" ABSOLUTE BASE_DIR "${PROJECT_SOURCE_DIR}")
    file(TO_CMAKE_PATH "${SINGLE_STEP_TESTS_DIR}" SINGLE_STEP_TESTS_DIR)
    set(SINGLE_STEP_TESTS_DIR "${SINGLE_STEP_TESTS_DIR}" PARENT_SCOPE)
endfunction()
