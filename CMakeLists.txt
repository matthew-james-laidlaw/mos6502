cmake_minimum_required(VERSION 4.2.1)

project(MOS6502 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

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

add_executable(klaus2m5 tests/klaus2m5/main.cpp)
target_link_libraries(klaus2m5 PRIVATE emulator)

# Locate the test ROM and bake it into the test executable
include(cmake/klaus2m5.cmake)
resolve_klaus2m5_rom_path()
target_compile_definitions(klaus2m5 PRIVATE KLAUS2M5_ROM_PATH=\"${KLAUS2M5_ROM_PATH}\")
