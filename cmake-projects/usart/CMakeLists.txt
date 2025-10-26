cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_VERBOSE_MAKEFILE ON)
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

#Project Definition
project(usart VERSION 0.1 LANGUAGES CXX)



# Collect all .cpp files inside src directory (non-recursive)
file(GLOB SRC_FILES "src/*.cpp")

# Add executable or library with collected source files
add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES})

# include external cmake modules

include(mcu_options.cmake)

# add_subdirectory(lib/gpio)
# add_subdirectory(lib/system)

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
        -nostdlib
        -Os
        -Wall
        # -fno-tree-vectorize
        # -fno-tree-loop-distribute-patterns
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
        -save-temps=obj
        # -fverbose-asm
)

# add flags for linker
target_link_options(${CMAKE_PROJECT_NAME} 
    PRIVATE
        -nostdlib
        -Wl,-Map=${CMAKE_PROJECT_NAME}.map,--gc-sections,-cref,--print-memory-usage
)

# link libraries with the executable
target_link_libraries(${CMAKE_PROJECT_NAME}
    PUBLIC
    # gpio
    # system
    mcu_options
)

# add target for flashing the micro-controller
add_custom_target(flash
    # COMMAND st-flash write ${CMAKE_PROJECT_NAME}.bin 0x8000000
     COMMAND STM32_Programmer_CLI -c port=SWD ap=0 -w ${CMAKE_PROJECT_NAME}.elf -rst
)

add_dependencies(flash ${CMAKE_PROJECT_NAME})

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    # COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.bin
)

if (CMAKE_EXPORT_COMPILE_COMMANDS)
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_SOURCE_DIR}/compile_commands.json
    )
endif()

function(dump_cmake_variables)
    get_cmake_property(variable_names VARIABLES)
    list(SORT variable_names)
    foreach(variable_name ${variable_names})
        message(STATUS "${variable_name}=${${variable_name}}")
    endforeach()
endfunction()

