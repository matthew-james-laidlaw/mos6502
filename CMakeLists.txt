cmake_minimum_required(VERSION 4.2.1)

project(MOS6502 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(nlohmann_json)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

if(WIN32)
    add_compile_options(/W4 /WX)
endif()

#    Core Emulator Library
# ---------------------------

add_library(emulator src/memory.cpp src/processor.cpp)
target_include_directories(emulator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

#    Klaus2M5 Test Suite
# -------------------------

add_executable(functional_test tests/functional_test/main.cpp)
target_link_libraries(functional_test PRIVATE emulator)

# Locate the test ROM and bake it into the test executable
include(cmake/klaus2m5.cmake)
resolve_klaus2m5_rom_path()
target_compile_definitions(functional_test PRIVATE KLAUS2M5_ROM_PATH=\"${KLAUS2M5_ROM_PATH}\")

#    SingleStepTests Suite
# ---------------------------

add_executable(single_step_tests tests/single_step_tests/main.cpp)
target_link_libraries(single_step_tests PRIVATE nlohmann_json::nlohmann_json)

# Locate the test JSON files and bake them into the test executable
include(cmake/single_step_tests.cmake)
resolve_single_step_tests_dir()
target_compile_definitions(single_step_tests PRIVATE SINGLE_STEP_TESTS_DIR=\"${SINGLE_STEP_TESTS_DIR}\")
