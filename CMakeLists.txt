cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)

set(projname "hello")

project(${projname} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

#include(example_auto_set_url.cmake)

add_executable(${projname}
        main.cpp
        extrafunc.cpp
        )

target_link_libraries(${projname} pico_stdlib hardware_spi)
pico_add_extra_outputs(${projname})

