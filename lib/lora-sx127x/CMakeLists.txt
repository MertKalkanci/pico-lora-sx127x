add_library(lora INTERFACE) 

target_sources(lora 
    INTERFACE 
      ${CMAKE_CURRENT_LIST_DIR}/lora.c
)

target_include_directories(lora 
    INTERFACE 
      ${CMAKE_CURRENT_LIST_DIR}
)
