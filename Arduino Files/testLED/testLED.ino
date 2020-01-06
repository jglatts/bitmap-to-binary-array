/*
	OLED Program for ESP8266
	@author: John G
*/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Bit_Maps.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/* Elapsed Time Variables */
int start = millis(), elapsed_time;
/* BitMap Image Variables */
const int boxWidth = display.width() - 2;
const int radius   = display.height() / 4;
const int xVal     = (display.width() - KUSH_WIDTH) / 2;
const int yVal     = (display.height() - KUSH_HEIGHT) / 2;
bool check;

/* Setup All Peripherals */
void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  displaySplash();
  delay(500);
  display.clearDisplay();
}

/* Main Loop */
void loop() {
  flashBitMap(check);
  displayTime();
  check = !check;
}

/* Flash some different BitMaps on the screen */
void flashBitMap(bool b) {
  (b) ? drawBitMap(kush, KUSH_WIDTH, KUSH_HEIGHT) : drawBitMap(birds, BIRDS_WIDTH, BIRDS_HEIGHT);
  delay(200);
}

/* Display Splash Screen Image */
void displaySplash() {
  display.clearDisplay();
  displayCircle();
  delay(2500);
  display.clearDisplay();
}

/* 
  Draw a bitmap from ROM at the given cordinates
  @param *img, binary array of bitmap
  @param w, width of bitmap
  @param *img, height of bitmap
*/
void drawBitMap(const uint8_t *img, int w, int h) {
  drawRectImg(w, h);
  display.drawBitmap(xVal, yVal, img, w, h, 1);
  display.display();
}

/* Draw a black rectangle to clear the BitMap */
void drawRectImg(int w, int h) {
  display.fillRoundRect(xVal, yVal , w, h, radius, SSD1306_BLACK);
  display.display();
}


/* Draw some filled in circles */
void displayCircle() {
  display.clearDisplay();
  for (int16_t i = 0; i < max(display.width(), display.height()) / 2; i += 2) {
    display.drawCircle(display.width() / 2, display.height() / 2, i, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  delay(1000);
}

/* Set the cursor and display text */
void displayText() {
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(3, 15);
  display.println(F("BIRDS!"));
  display.setCursor(97, 6);
  display.println(F("Time:"));
  display.display();
}

/* Set the cursor and display the given time */
void displayTime() {
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(97, 18);
  display.print(getMins());
  display.print(":");
  display.print(getSecs());
  display.display();
  drawRectText();
}

/* Return the elapsed minutes */
int getMins() {
  elapsed_time = millis() - start;
  return int(elapsed_time / 60000);
}

/* Return the elapsed seconds */
int getSecs() {
  return int((elapsed_time % 60000)/1000);
}

/* Draw a black rectangle to clear certain the Time text */
void drawRectText() {
  display.fillRoundRect(90, 18, boxWidth, 10, radius, SSD1306_BLACK);
  display.display();
}

/*
  Animate a bitmap image from ROM
  @param *img, binary array of bitmap
  @param w, width of bitmap
  @param *img, height of bitmap
*/
void testanimate(const uint8_t* bitmap, uint8_t w, uint8_t h) {
  int8_t f, icons[NUMFLAKES][3];
  // Initialize positions
  for (f = 0; f < NUMFLAKES; f++) {
    icons[f][XPOS] = random(1 - KUSH_WIDTH, display.width());
    icons[f][YPOS] = -KUSH_HEIGHT;
    icons[f][DELTAY] = random(1, 6);
  }
  for (;;) { // Loop forever...
    display.clearDisplay(); // Clear the display buffer
    // Draw each snowflake:
    for (f = 0; f < NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SSD1306_WHITE);
    }
    display.display(); // Show the display buffer on the screen
    delay(110);        // Pause for 1/10 second
    // Then update coordinates
    for (f = 0; f < NUMFLAKES; f++) {
      icons[f][YPOS] += icons[f][DELTAY];
      // If snowflake is off the bottom of the screen...
      if (icons[f][YPOS] >= display.height()) {
        // Reinitialize to a random position, just off the top
        icons[f][XPOS] = random(1 - KUSH_WIDTH, display.width());
        icons[f][YPOS] = -KUSH_HEIGHT;
        icons[f][DELTAY] = random(1, 6);
      }
    }
  }
}
