cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(lora-sx127x-demo C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_compile_options(-Wall -Wno-unused-function)

add_subdirectory(lora-sx127x)
add_subdirectory(receive-demo)
add_subdirectory(send-demo)