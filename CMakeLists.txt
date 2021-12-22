cmake_minimum_required(VERSION 3.13)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(morseCode C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()
add_executable(morseCode
  main.cpp
)
pico_add_extra_outputs(morseCode)
target_link_libraries(morseCode pico_stdlib)