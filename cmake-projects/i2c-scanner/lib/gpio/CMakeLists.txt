set(LIB_NAME gpio)

# Need the MCU options to be defined for compilation
if(NOT TARGET mcu_options)
    message(FATAL_ERROR "Target mcu_options is not defined!")
else()
    get_target_property(type mcu_options TYPE)
    if(NOT type STREQUAL "INTERFACE_LIBRARY")
        message(FATAL_ERROR "Target mcu_options must be an INTERFACE library!")
    endif()
endif()

# specify name of library
add_library(${LIB_NAME} "")


# add sources for library
target_sources(${LIB_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/gpio_port.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gpio_pin.cpp
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/gpio_port.h
    ${CMAKE_CURRENT_LIST_DIR}/gpio_pin.h
)

# add this path to include directories for the target
target_include_directories(${LIB_NAME}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${LIB_NAME}
    PRIVATE
    mcu_options
)
