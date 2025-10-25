cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Toolchain configuration
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(TOOLCHAIN_PREFIX arm-none-eabi)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}-objcopy)
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}-size)
set(CMAKE_OBJDUMP ${TOOLCHAIN_PREFIX}-objdump)

set(CMAKE_EXECUTABLE_SUFFIX_ASM ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX ".elf")

# Language Features
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS ON)

# Clear any platform default flags
set(CMAKE_C_FLAGS "" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "" CACHE STRING "" FORCE)
set(CMAKE_CXX_LINK_FLAGS "" CACHE STRING "" FORCE)

# MCU configuration
set(MCU_FAMILY STM32F401xE)
set(MCU_LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/stm32f4.ld)
set(MCU_FLAGS
    -mcpu=cortex-m4
    -mthumb
    -mfloat-abi=soft
)

#Project Definition
project(blink VERSION 0.1 LANGUAGES CXX)


# Collect all .cpp files inside src directory (non-recursive)
file(GLOB SRC_FILES "src/*.cpp")

# Add executable or library with collected source files
add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES})

#Definition
target_compile_definitions(${CMAKE_PROJECT_NAME}
    PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
        ${MCU_FAMILY}
)

# add directories to look for header files
target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Flags
set(CMAKE_CXX_FLAGS_DEBUG
    "-g -gdwarf-2"
)

# add flags for compiler
target_compile_options(${CMAKE_PROJECT_NAME}
    PRIVATE
        ${MCU_FLAGS}
        -nostdlib
        -Os
        -Wall
        -fno-tree-loop-distribute-patterns
        -fdata-sections
        -ffunction-sections
        # -fno-unwind-tables
        # -fno-asynchronous-unwind-tables
        # -Wall
        # -Wextra
        # -Wpedantic
        # -Wdouble-promotion
        # -Wformat=2
        # -Wformat-truncation
        # -Wundef
        # -fno-common
        -fno-exceptions
        -fno-rtti
        # -Wconversion # STM libraries!
        # -Wno-volatile
        # -Wold-style-cast
        # -Wuseless-cast
        # -Wsuggest-override
)

# add flags for linker
target_link_options(${CMAKE_PROJECT_NAME} 
    PRIVATE
        -T ${MCU_LINKER_SCRIPT}
        -nostdlib
        ${MCU_FLAGS}
        -Wl,-Map=${CMAKE_PROJECT_NAME}.map,--gc-sections,-cref,--print-memory-usage
)

# add target for flashing the micro-controller
add_custom_target(flash
    COMMAND st-flash write ${CMAKE_PROJECT_NAME}.bin 0x8000000
)

add_dependencies(flash ${CMAKE_PROJECT_NAME})

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.bin
)

add_custom_command(
    OUTPUT ${CMAKE_SOURCE_DIR}/compile_commands.json
    COMMAND ${CMAKE_COMMAND} -E ln -sf ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json
    DEPENDS ${CMAKE_BINARY_DIR}/compile_commands.json
)

add_custom_target(
    symlink-compile-commands ALL
    DEPENDS ${CMAKE_SOURCE_DIR}/compile_commands.json
)

function(dump_cmake_variables)
    get_cmake_property(variable_names VARIABLES)
    list(SORT variable_names)
    foreach(variable_name ${variable_names})
        message(STATUS "${variable_name}=${${variable_name}}")
    endforeach()
endfunction()

