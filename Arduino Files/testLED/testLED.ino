#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Bit_Maps.h"

#define SCREEN_WIDTH  128 
#define SCREEN_HEIGHT 32 
#define OLED_RESET    -1 
#define XPOS          0 
#define YPOS          1
#define DELTAY        2
// smiley is 40x40
// also try 80x20
#define LOGO_HEIGHT   40
#define LOGO_WIDTH    40

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); 
  }
  displaySplash();
}

void loop() {
  testdrawbitmap();
  testFonts();
}

void displaySplash() {
  display.clearDisplay();
  delay(1000);
  testdrawcircle();
  delay(2500);
  display.clearDisplay();
}

void testscrolltext(void) {
  display.clearDisplay();
  display.setTextSize(2); // set text-scale
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("TURN UP!"));
  display.display();      // Show initial text
  delay(100);
  // Scroll in various directions, pausing in-between:
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  delay(1000);
}

void testdrawcircle(void) {
  display.clearDisplay();
  for(int16_t i=0; i<max(display.width(),display.height())/2; i+=2) {
    display.drawCircle(display.width()/2, display.height()/2, i, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  delay(2000);
}

void testFonts() {
  //display.clearDisplay();
  display.setTextSize(1); 
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(95, 0);
  display.println(F("Ayoo"));
  display.setCursor(95, 15);
  display.println(F("Foo!"));
  display.display();      // Show initial text
}

void testdrawbitmap(void) {
  //display.clearDisplay();
  int xVal = (display.width() - LOGO_WIDTH) / 2;
  display.drawBitmap(xVal, 0, smiley, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}
