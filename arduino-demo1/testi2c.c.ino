
#include <Wire.h>
#include <stdio.h>

#define I2CADDR 0x3F

int value = 1234;
// Has the lowest byte been sent
bool lower_sent = false;

void setup() {
  Wire.begin(I2CADDR);          // join i2c bus 
  Wire.onRequest(requestEvent); // register event - request data from arduino
  Wire.onReceive(receiveEvent); // register event - receive data at arduino

  // Serial monitor for debugging
  Serial.begin(9600);
  Serial.println("Starting");
}

void loop() {
  delay(100);
}

void receiveEvent(int bytes_recv) {
  // If received 0 bytes then detect or similar
  if (bytes_recv < 2) return;
  // Create array big enough for all data
  byte received_data[bytes_recv];
  int byte_num = 0;
  while (Wire.available() > 0) {
    received_data[byte_num] = Wire.read();
    byte_num ++;
  }
  int received_number = received_data[0] + (received_data[1] << 8);
  char buffer[20];
  sprintf (buffer, "Read data %d\n", received_number);
  Serial.println(buffer);
    
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  int byte_value;

  if (lower_sent == false) {
    byte_value = value & 0xff;
    lower_sent = true; 
  }
  else {
    byte_value = value >> 8;
    lower_sent = false;
  }

  Wire.write(byte_value);
  
}
