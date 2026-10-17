function(resolve_klaus2m5_rom_path)
    set(KLAUS2M5_ROM "" CACHE FILEPATH "Path to the Klaus 6502 functional test ROM")
    if(NOT KLAUS2M5_ROM)
        find_file(KLAUS2M5_ROM_DEFAULT
            NAMES 6502_functional_test.bin
            PATHS "${PROJECT_SOURCE_DIR}/tests/klaus2m5"
            NO_DEFAULT_PATH
        )
        if(NOT KLAUS2M5_ROM_DEFAULT)
            message(FATAL_ERROR "Could not find 6502_functional_test.bin in tests/klaus2m5")
        endif()
        set(KLAUS2M5_ROM "${KLAUS2M5_ROM_DEFAULT}")
    endif()

    if(NOT EXISTS "${KLAUS2M5_ROM}")
        message(FATAL_ERROR "KLAUS2M5_ROM does not exist: ${KLAUS2M5_ROM}")
    endif()

    file(TO_CMAKE_PATH "${KLAUS2M5_ROM}" KLAUS2M5_ROM_PATH)
    set(KLAUS2M5_ROM_PATH "${KLAUS2M5_ROM_PATH}" PARENT_SCOPE)
endfunction()
