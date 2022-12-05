# Write your code here :-)
import smbus
from time import sleep

# I2C channel 1 is connected to the GPIO pins
channel = 1
address = 0x3F

# Initialize I2C (SMBus)
bus = smbus.SMBus(channel)

rx_bytes = [0,0]

i=1000
while 1:
    print ("Start loop "+str(i))
    sleep (1)
    try:
        print ("Writing data "+str(i))
        # Write out I2C command: address, byte0, msg[0]
        bus.write_i2c_block_data(address, i&0xff, [i>>8])
    except Exception as e:
        print ("Writing Error "+str(e))
        continue
    read = 0
    while read == 0:
        try:
            print ("Reading data")
            #rx_bytes = bus.read_i2c_block_data(address, 7, 1)
            rx_bytes[0] = bus.read_byte(address);
            rx_bytes[1] = bus.read_byte(address);
        except Exception as e:
            print ("Read Error "+str(e))
            continue
        read = 1
    print ("Read "+str(rx_bytes))
    value = rx_bytes[0] + (rx_bytes[1] << 8)
    print ("Read value "+str(value))
    i+=1