cmake_minimum_required(VERSION 4.2.1)

project(MOS6502 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

add_executable(emulator src/main.cpp src/memory.cpp src/processor.cpp)
target_include_directories(emulator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
