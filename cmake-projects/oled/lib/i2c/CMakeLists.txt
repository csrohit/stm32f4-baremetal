#specify name of library
set(LIB_NAME i2c)
add_library(${LIB_NAME} "")

# Need the MCU options to be defined for compilation
if(NOT TARGET mcu_options)
    message(FATAL_ERROR "Target mcu_options is not defined!")
else()
    get_target_property(type mcu_options TYPE)
    if(NOT type STREQUAL "INTERFACE_LIBRARY")
        message(FATAL_ERROR "Target mcu_options must be an INTERFACE library!")
    endif()
endif()

if(NOT TARGET system)
    message(FATAL_ERROR "Target system is not defined!")
endif()

# add sources for library
target_sources(${LIB_NAME}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/i2c.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/i2c.h
)

# add this path to include directories for the target
target_include_directories(${LIB_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${LIB_NAME}
    PRIVATE
    mcu_options
    system
)


