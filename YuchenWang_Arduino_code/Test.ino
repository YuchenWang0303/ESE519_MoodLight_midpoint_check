// testshapes demo for Adafruit RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 16x32 RGB LED matrix:
// http://www.adafruit.com/products/420

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

#include <RGBmatrixPanel.h>

// Most of the signal pins are configurable, but the CLK pin has some
// special constraints.  On 8-bit AVR boards it must be on PORTB...
// Pin 8 works on the Arduino Uno & compatibles (e.g. Adafruit Metro),
// Pin 11 works on the Arduino Mega.  On 32-bit SAMD boards it must be
// on the same PORT as the RGB data pins (D2-D7)...
// Pin 8 works on the Adafruit Metro M0 or Arduino Zero,
// Pin A4 works on the Adafruit Metro M4 (if using the Adafruit RGB
// Matrix Shield, cut trace between CLK pads and run a wire to A4).

#define CLK  8   // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.
//#define CLK A4 // USE THIS ON METRO M4 (not M0)
//#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);
void draw_smile_face();
void draw_cry_face();
void setup() {

  matrix.begin();


}

void loop() {
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  draw_smile_face();
  matrix.setCursor(18, 1);  // start at top left, with one pixel of spacing
  matrix.setTextSize(2);   // size 1 == 8 pixels high

  // print each letter with a rainbow color
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.print('$');
  delay(1000);
  
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  
  matrix.setCursor(18, 1);  // start at top left, with one pixel of spacing
  matrix.setTextSize(2);   // size 1 == 8 pixels high

  // print each letter with a rainbow color
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.print('#');
  draw_cry_face();
  delay(1000);
  matrix.fillScreen(matrix.Color333(0, 0, 0));

  // draw some text!
  matrix.setCursor(1, 0);  // start at top left, with one pixel of spacing
  matrix.setTextSize(1);   // size 1 == 8 pixels high

  // print each letter with a rainbow color
  matrix.setTextColor(matrix.Color333(0,0,7));
  matrix.print('U');
  matrix.setTextColor(matrix.Color333(0,0,7));
  matrix.print('P');
  matrix.setTextColor(matrix.Color333(0,0,7));
  matrix.print('E');
  matrix.setTextColor(matrix.Color333(0,0,7));
  matrix.print('N');
  matrix.setTextColor(matrix.Color333(0,0,7));
  matrix.print('N');
  
  matrix.setCursor(1, 8);  // next line
  matrix.setTextColor(matrix.Color333(7,0,0));
  matrix.print('T');
  matrix.setTextColor(matrix.Color333(7,0,0));
  matrix.print('R');
  matrix.setTextColor(matrix.Color333(7,0,0));
  matrix.print('A');
  matrix.setTextColor(matrix.Color333(7,0,0));
  matrix.print('S');
  matrix.setTextColor(matrix.Color333(7,0,0));
  matrix.print('H');
  delay(1500);

  
  matrix.fillScreen(matrix.Color333(0, 0, 0));

  // draw some text!
  matrix.setCursor(11, 1);  // start at top left, with one pixel of spacing
  matrix.setTextSize(2);   // size 1 == 8 pixels high
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.print('6');

  delay(1500);
  // whew!

}
void draw_smile_face(){

  matrix.drawCircle(7, 7, 7, matrix.Color333(7, 7, 0));
  matrix.drawPixel(4-2, 6-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(5-2, 5-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(7-2, 6-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(6-2, 5-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(9, 6-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(10, 5-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(12, 6-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(11, 5-1, matrix.Color333(7, 0, 0));
 
  // fill a violet circle
  //matrix.fillCircle(23, 7, 7, matrix.Color333(7, 7, 0));
  matrix.drawLine(6, 11, 8, 11, matrix.Color333(7, 0, 0));
  matrix.drawPixel(5, 10, matrix.Color333(7, 0, 0));
  matrix.drawPixel(9, 10, matrix.Color333(7, 0, 0));
}

void draw_cry_face(){
  
  matrix.drawCircle(7, 7, 7, matrix.Color333(7, 0, 0));
  matrix.drawPixel(4-2, 6-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(5-2, 5-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(7-2, 6-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(6-2, 5-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(9, 6-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(10, 5-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(12, 6-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(11, 5-1, matrix.Color333(7, 0, 0));
 
  // fill a violet circle
  //matrix.fillCircle(23, 7, 7, matrix.Color333(7, 7, 0));
  matrix.drawLine(6, 11-1, 8, 11-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(5, 12-1, matrix.Color333(7, 0, 0));
  matrix.drawPixel(9, 12-1, matrix.Color333(7, 0, 0));
  }
