# ESE519_MoodLight_midpoint_check
University of Pennsylvania, ESE 5190: Intro to Embedded Systems, Midpoint Write up

## YuchenWang Worked with KatrinaJi, and Ryan Zhang

---

    Yuchen Wang
    wangybv@seas.upenn.edu
    Tested on:  MacBook Pro (14-inch, 2021), macOS Monterey 12.6
    
    Katrina Ji
    katji@seas.upenn.edu
    Tested on:  MacBook Pro (14-inch, 2021), macOS Monterey 12.6
        
    Ryan Zhang
    zcy6@seas.upenn.edu
    Tested on:  Lenovo LEGION R900X, Windows 11
    
---
# Main Components List:

1. 32*16 LED Matrix
2. Arduino Uno Rev3
3. QTPY-2040 $\times 2$ 
4. Push button $\times 2$
5. Pico4ML 
6. Jump wires $\times several$

# System Block Diagram (tentative)

![image](https://user-images.githubusercontent.com/114244957/205533634-17c1f83d-3089-485c-bd35-ca45749efef0.png)

---
## Yuchen Wang

### Overview

My main responsibility is to use PIO to drive the SHT40(Temp and Humidity) sensor and be able to calculate the indoor temperature and humidity. In addition, I will also explore with my teammates how to use the I2C protocol to transfer data between the two microcontrollers(QTPY-2040 and Arduino). Finally, I am going to try to drive a 32*16 LED matrix with Arduino, and use a QTPY2040 to control the Arduino via I2C, so that the LED matrix can output the desired messages. Also, I attempt to use a push button that will change what is displayed on the LED matrix screen when I press it, such as if I press it the first time to show the current temperature and humidity in the room, if I press it the second time to show the sensory temperature, and if I press it the third time to show some suggestions for improving the current environment etc.

- Drive SHT40 via PIO
- Drive LED Matrix with Arduino
- Toggle the LED Matrix
- Explore I2C communication between different microcontrollers

### Complete Parts

- Drive SHT40 via PIO    

<img width="1082" alt="Screen Shot 2022-12-03 at 01 24 01" src="https://user-images.githubusercontent.com/105755054/205427904-cedf852a-e943-4740-8846-f1cd3dd4b8c6.png">

![IMG_0128](https://user-images.githubusercontent.com/105755054/205427931-90be43fd-b95c-46dd-99fa-9b7082613c2f.GIF)

Pressing BOOT PIN is for simulating that people are detected.

- Drive LED Matrix with Arduino

![IMG_0138](https://user-images.githubusercontent.com/105755054/205474897-44317ec7-11a4-4ce1-8099-91ec8ab0e3a2.GIF)

### Next Step

- Connecting Arduino and QTPY2040 via I2C protocal 

### Mind Guide Diagram

![WechatIMG7533](https://user-images.githubusercontent.com/105755054/205474876-253712ba-c986-43c4-bd62-c45cd8241121.jpeg)

---

## Katrina Ji

### Overview
I am responsible for initiating the new Pico4ML and enable the person detection part. Besides that, I will also alterate the output according to the requirement from the main PR2040 board. (At first, we are thinking using I2C to transmit the person detection score; for now, we plan to use ```gpio``` and transmit a high and low voltage to indicate person detection.) Reference: [pico4ML](https://github.com/ArduCAM/pico-tflmicro.git)

We have also looked detailed into I2C communication between two boards. For now, we can communicate I2C using a single board. But the functions should be universal for multiple boards. Reference: [pico_i2c_git](https://github.com/vmilea/pico_i2c_slave.git), [pico_Arduino_i2c](http://www.penguintutor.com/electronics/i2c) 

- Comb and refine flow diagrams for the project
- Enable Pico4ML and achieve person detection
- Explore I2C communication between different microcontrollers

### Complete Parts

- Comb and refine flow diagrams for the project
Updated block diagram is shown in the front. Flow diagrams are also shown in this readme file.

- Enable Pico4ML and achieve person detection

The screen on the Pico4ML will show the camera capture and return a percentage.

![IMG_0319](https://user-images.githubusercontent.com/114244957/205535926-137e147b-4f77-4aac-be11-3cecd027b888.GIF)

![personscore_ini](https://user-images.githubusercontent.com/114244957/205536462-63c5ff46-3279-43d3-b6e9-0e3858d88507.png)

The REPL will give a "person score" and a "no person score". When there is a person detected, the "person score" will be above 100. Our team will only use the "person score" as the main indicator. An output will be toggled when the socre is high and the high/low voltage change will be captured by the main RP2040 board as singal input.

- Explore I2C communication between different microcontrollers

We have successfully enable I2C communication as the master and slave from the same board. We wired pin 28 to 26 (SDA), and pin 29 to 27 (SCL). For Pico4Ml, the pins are shown as comments. The demo code shows the case where a Pico4ML and an RP2040 wire together.
```
static const uint I2C_SLAVE_SDA_PIN = 28;// pico4ml 12, qtpy 28 
static const uint I2C_SLAVE_SCL_PIN = 29;// pico4ml 13, qtpy 29 
static const uint I2C_MASTER_SDA_PIN = 10;//pico4ml 10, qtpy 26
static const uint I2C_MASTER_SCL_PIN = 11;//pico4ml 11, qtpy 27
```
The REPL gave a snapshot of what's happening.

![image](https://user-images.githubusercontent.com/114244957/205537639-44df3dd5-3370-4afe-963c-acfd5ba983cf.png)

### Next Step

- Connect Pico4ML and RP2040 using  ```gpio```
- Help connect Arduino and QTPY2040 via I2C protocal
- Refine the demo for final presentation

### Mind Guide Diagram

![IMG_0687](https://user-images.githubusercontent.com/114244957/205533466-29ab1a73-8744-4eab-a0f1-ba1548986a68.jpg)

---

## Ryan Zhang

### Overview

My main responsibility is connecting LCD screen and QT-PY2040. I am trying to research how to show the specific patterns on the LCD screen based on the input data transfered via I2C protocol. Besides, I will solder the PCB based on the designed circuit in order to have the integral product.

- LCD screen
- Solder the PCB
