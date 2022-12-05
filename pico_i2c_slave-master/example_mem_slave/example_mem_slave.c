/*
 * Copyright (c) 2021 Valentin Milea <valentin.milea@gmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <i2c_fifo.h>
#include <i2c_slave.h>
#include <pico/stdlib.h>
#include <stdio.h>
#include <string.h>

static const uint I2C_SLAVE_ADDRESS = 0x17;
static const uint I2C_BAUDRATE = 100000; // 100 kHz

// For this example, we run both the master and slave from the same board.
// You'll need to wire pin 28 to 26 (SDA), and pin 29 to 27 (SCL).
// I will use pico4ml as master and qtpy 2040 as slave.
static const uint I2C_SLAVE_SDA_PIN = 28;// pico4ml 12, qtpy 28 
static const uint I2C_SLAVE_SCL_PIN = 29;// pico4ml 13, qtpy 29 
static const uint I2C_MASTER_SDA_PIN = 10;//pico4ml 10, qtpy 26
static const uint I2C_MASTER_SCL_PIN = 11;//pico4ml 11, qtpy 27

// The slave implements a 256 byte memory. To write a series of bytes, the master first
// writes the memory address, followed by the data. The address is automatically incremented
// for each byte transferred, looping back to 0 upon reaching the end. Reading is done
// sequentially from the current memory address.
static struct
{
    uint8_t mem[256];
    uint8_t mem_address;
    bool mem_address_written;
} context;

// Our handler is called from the I2C ISR, so it must complete quickly. Blocking calls /
// printing to stdio may interfere with interrupt handling.
static void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event) {
    switch (event) {
    case I2C_SLAVE_RECEIVE: // master has written some data
        if (!context.mem_address_written) {
            // writes always start with the memory address
            context.mem_address = i2c_read_byte(i2c);
            context.mem_address_written = true;
        } else {
            // save into memory
            context.mem[context.mem_address] = i2c_read_byte(i2c);
            context.mem_address++;
        }
        break;
    case I2C_SLAVE_REQUEST: // master is requesting data
        // load from memory
        i2c_write_byte(i2c, context.mem[context.mem_address]);
        context.mem_address++;
        break;
    case I2C_SLAVE_FINISH: // master has signalled Stop / Restart
        context.mem_address_written = false;
        break;
    default:
        break;
    }
}

static void setup_slave() {
    gpio_init(I2C_SLAVE_SDA_PIN);
    gpio_set_function(I2C_SLAVE_SDA_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SLAVE_SDA_PIN);

    gpio_init(I2C_SLAVE_SCL_PIN);
    gpio_set_function(I2C_SLAVE_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SLAVE_SCL_PIN);

    i2c_init(i2c0, I2C_BAUDRATE);
    // configure I2C0 for slave mode
    i2c_slave_init(i2c0, I2C_SLAVE_ADDRESS, &i2c_slave_handler);
    printf("Setup_salve Success.\n");
}

static void run_master() {
    gpio_init(I2C_MASTER_SDA_PIN);
    gpio_set_function(I2C_MASTER_SDA_PIN, GPIO_FUNC_I2C);
    // pull-ups are already active on slave side, this is just a fail-safe in case the wiring is faulty
    gpio_pull_up(I2C_MASTER_SDA_PIN);

    gpio_init(I2C_MASTER_SCL_PIN);
    gpio_set_function(I2C_MASTER_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_MASTER_SCL_PIN);

    i2c_init(i2c1, I2C_BAUDRATE);

    for (uint8_t mem_address = 0;; mem_address = (mem_address + 32) % 256) {
        char msg[32];
        snprintf(msg, sizeof(msg), "Hello, I2C slave! - 0x%02X", mem_address);
        uint8_t msg_len = strlen(msg);

        uint8_t buf[32];
        buf[0] = mem_address;
        memcpy(buf + 1, msg, msg_len);
        // write message at mem_address
        printf("Write at 0x%02X: '%s'\n", mem_address, msg);
        int count = i2c_write_blocking(i2c1, I2C_SLAVE_ADDRESS, buf, 1 + msg_len, false);
        if (count < 0) {
            puts("Couldn't write to slave, please check your wiring!");
            return;
        }
        hard_assert(count == 1 + msg_len);

        // seek to mem_address
        count = i2c_write_blocking(i2c1, I2C_SLAVE_ADDRESS, buf, 1, true);
        hard_assert(count == 1);
        // partial read
        uint8_t split = 5;
        count = i2c_read_blocking(i2c1, I2C_SLAVE_ADDRESS, buf, split, true);
        hard_assert(count == split);
        buf[count] = '\0';
        printf("Read  at 0x%02X: '%s'\n", mem_address, buf);
        hard_assert(memcmp(buf, msg, split) == 0);
        // read the remaining bytes, continuing from last address
        count = i2c_read_blocking(i2c1, I2C_SLAVE_ADDRESS, buf, msg_len - split, false);
        hard_assert(count == msg_len - split);
        buf[count] = '\0';
        printf("Read  at 0x%02X: '%s'\n", mem_address + split, buf);
        hard_assert(memcmp(buf, msg + split, msg_len - split) == 0);

        puts("");
        sleep_ms(2000);
    }
}

int main() {
    stdio_init_all();
    while(stdio_usb_connected()!= true);
    puts("I2C slave example");
    printf("I'm slave.\n");

    setup_slave();
    // run_master();
}