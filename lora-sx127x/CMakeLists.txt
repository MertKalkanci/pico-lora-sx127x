add_library(lora-sx127x INTERFACE) 

target_sources(lora-sx127x 
    INTERFACE 
      ${CMAKE_CURRENT_LIST_DIR}/lora.c
)
