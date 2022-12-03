# ESE519_MoodLight_midpoint_check
University of Pennsylvania, ESE 5190: Intro to Embedded Systems, Midpoint Write up

## YuchenWang Worked with KatrinaJi, Ryan Zhang

---

    Yuchen Wang
    wangyuchen0303@gmail.com
    Tested on:  MacBook Pro (14-inch, 2021), macOS Monterey 12.6
    
    Katrina Ji
    katji@seas.upenn.edu
    Tested on:  MacBook Pro (14-inch, 2021), macOS Monterey 12.6
        
    Ryan Zhang
    zcy6@seas.upenn.edu
    Tested on:  Lenovo LEGION R900X, Windows 11
    
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

### Next Step

- Drive LED Matrix with Arduino

### Diagram

---

## Katrina Ji


---

## Ryan Zhang

### Overview

My main responsibility is connecting LCD screen and QT-PY2040. I am trying to research how to show the specific patterns on the LCD screen based on the input data transfered via I2C protocol. Besides, I will solder the PCB based on the designed circuit in order to have the integral product.

- LCD screen
- Solder the PCB
