# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico-linear-encoder.c C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(pico-linear-encoder.c example.c )

pico_set_program_name(pico-linear-encoder.c "pico-linear-encoder.c")
pico_set_program_version(pico-linear-encoder.c "0.1")

pico_enable_stdio_uart(pico-linear-encoder.c 1)
pico_enable_stdio_usb(pico-linear-encoder.c 0)

# Add the standard library to the build
target_link_libraries(pico-linear-encoder.c pico_stdlib hardware_adc)

pico_add_extra_outputs(pico-linear-encoder.c)
