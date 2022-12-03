#include <stdio.h>
#include "pico/stdlib.h"
#include "pio_i2c.h"
#include <math.h>
#include "hardware/gpio.h"
#include "sht4x.h"

#define SDA 22
#define SCL 23

#define QTPY_BOOT_PIN 21
const int addr = 0x44;

PIO pio = pio0;
uint sm = 0;

//get the temp. and humidity from sensor
void get_sensor(){
    int32_t temp;
    int32_t hum;
    read_temp_hum(&temp , &hum, pio, sm, addr);
    printf("temperature: %d\n", temp);
    printf("humidity: %d\n", hum);
    sleep_ms(50);
}

//main loop
int main(){
    stdio_init_all();
    gpio_init(QTPY_BOOT_PIN);
    gpio_set_dir(QTPY_BOOT_PIN, GPIO_IN);
    while(stdio_usb_connected()!=true);
    uint offset = pio_add_program(pio, &i2c_program);
    i2c_program_init(pio, sm, offset, SDA, SCL);
    while(true){
        if(gpio_get(QTPY_BOOT_PIN) == 0){
            get_sensor();
        }
    }
}