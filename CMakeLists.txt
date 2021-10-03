add_executable(mcp3002 mcp3002.c)
target_link_libraries(mcp3002 pico_stdlib hardware_spi hardware_adc)

pico_enable_stdio_usb(mcp3002 1)
pico_enable_stdio_uart(mcp3002 0)

pico_add_extra_outputs(mcp3002)