cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(lora-sx127x-demo C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
include_directories(${CMAKE_CURRENT_LIST_DIR}/lora-sx127x)
add_subdirectory(lora-sx127x)

add_executable(${PROJECT_NAME}
    example.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(${PROJECT_NAME} 
    pico_stdlib
    hardware_gpio
    hardware_uart
    hardware_irq
    lora-sx127x
    )

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(${PROJECT_NAME})


# Enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)