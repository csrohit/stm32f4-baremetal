# mcu_options.cmake

# Define the INTERFACE library (only if not already defined)
if(NOT TARGET mcu_options)
    add_library(mcu_options INTERFACE)
endif()

# MCU configuration
set(MCU_FAMILY STM32F401xE)
set(MCU_LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/stm32f4.ld)

# Add compile options (example: for ARM Cortex-M, size optimization, warning level)
target_compile_options(mcu_options
INTERFACE
    $<$<CONFIG:Debug>:-g -gdwarf-2 -O0>
    -mcpu=cortex-m4
    -mthumb
    -Wall
)

# Add compile definitions (example: MCU family macro)
target_compile_definitions(mcu_options
INTERFACE
    ${MCU_FAMILY}
)

target_include_directories(mcu_options
INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_options(mcu_options
INTERFACE
    -T ${MCU_LINKER_SCRIPT}
)
