# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Inicialização do pico_sdk
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()

set(PICO_BOARD pico_w CACHE STRING "Board type")

include(pico_sdk_import.cmake)

project(embarcatech_dma C CXX ASM)

pico_sdk_init()

# Configuração do executável dma_irq
add_executable(dma_irq dma_irq.c)
pico_set_program_name(dma_irq "embarcatech_dma_irq")
pico_set_program_version(dma_irq "0.1")
pico_enable_stdio_uart(dma_irq 0)
pico_enable_stdio_usb(dma_irq 1)
target_link_libraries(dma_irq pico_stdlib hardware_dma hardware_adc)
target_include_directories(dma_irq PRIVATE ${CMAKE_CURRENT_LIST_DIR})
pico_add_extra_outputs(dma_irq)

# Configuração do executável dma_blocking
add_executable(dma_blocking dma_blocking.c)
pico_set_program_name(dma_blocking "embarcatech_dma_blocking")
pico_set_program_version(dma_blocking "0.2")
pico_enable_stdio_uart(dma_blocking 0)
pico_enable_stdio_usb(dma_blocking 1)
target_link_libraries(dma_blocking pico_stdlib hardware_dma hardware_adc)
target_include_directories(dma_blocking PRIVATE ${CMAKE_CURRENT_LIST_DIR})
pico_add_extra_outputs(dma_blocking)
