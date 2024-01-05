cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# rest of your project
add_executable(lora-sx127x-demo-receive
example.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(lora-sx127x-demo-receive
PRIVATE
    pico_stdlib
    hardware_gpio
    hardware_uart
    hardware_irq
    lora
    )

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(lora-sx127x-demo-receive)


# Enable usb output, disable uart output
pico_enable_stdio_usb(lora-sx127x-demo-receive 1)
pico_enable_stdio_uart(lora-sx127x-demo-receive 0)