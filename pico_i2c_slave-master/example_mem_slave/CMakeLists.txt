add_executable(example_mem_slave example_mem_slave.c)

pico_enable_stdio_uart(example_mem_slave 1)
pico_enable_stdio_usb(example_mem_slave 1)

pico_add_extra_outputs(example_mem_slave)

target_compile_options(example_mem_slave PRIVATE -Wall)

target_link_libraries(example_mem_slave i2c_slave pico_stdlib)
