/*
  Get the overwrite text working
  - have to clear just a small section of the LED
*/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Bit_Maps.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/* Time Counters */
int start = millis(), elapsed_time;

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  displaySplash();
  drawBitMap();
}

void loop() {
  displayTime();
}

void displaySplash() {
  display.clearDisplay();
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
  for (int16_t i = 0; i < max(display.width(), display.height()) / 2; i += 2) {
    display.drawCircle(display.width() / 2, display.height() / 2, i, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  delay(1000);
}

void testFonts() {
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(95, 3);
  display.println(F("Kush"));
  display.setCursor(95, 10);
  display.println(F("Foo.."));
  display.display();
}

void displayTime() {
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(93, 18);
  display.print(getMins());
  display.print(":");
  display.print(getSecs());
  display.display();
  delay(300);
  drawRect();
}

void clearLine() {
  display.drawFastHLine(30, 14, 100, SSD1306_BLACK);
  display.drawFastHLine(31, 14, 100, SSD1306_BLACK);
  display.drawFastHLine(32, 14, 100, SSD1306_BLACK);
  display.drawFastHLine(33, 14, 100, SSD1306_BLACK);
  display.display();
}

void drawBitMap() {
  int xVal, yVal;
  display.clearDisplay();
  xVal = (display.width() - KUSH_WIDTH) / 2;
  yVal = (display.height() - KUSH_HEIGHT) / 2;
  display.drawBitmap(xVal, yVal, kush, KUSH_WIDTH, KUSH_HEIGHT, 1);
  display.display();
}

int getMins() {
  elapsed_time = millis() - start;
  return int(elapsed_time / 60000);
}

int getSecs() {
  int mod = elapsed_time % 60000;
  return int(mod / 1000);
}

void testdrawrect(void) {
  display.clearDisplay();
  for (int16_t i = 0; i < display.height() / 2; i += 2) {
    display.drawRect(i, i, display.width() - 2 * i, display.height() - 2 * i, SSD1306_WHITE);
    display.display(); // Update screen with each newly-drawn rectangle
    delay(1);
  }
  delay(2000);
}

void drawRect(void) {
  int xVal = display.width() - 2;
  int radius = display.height() / 4;
  display.fillRoundRect(90, 18, xVal, 10, radius, SSD1306_BLACK);
  display.display();
}
