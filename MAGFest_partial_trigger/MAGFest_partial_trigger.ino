/* ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Arsenio Dev wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. 
 * ----------------------------------------------------------------------------
 */
//Passive activity is breathing LEDs, on trigger cue strobe firing

#include <WS2812FX.h>
#include <DFRobotDFPlayerMini.h>

#define LED_COUNT 5 //How many LEDS
#define LED_PIN 8 //data pin
#define TRIGGER 2 //trigger button
#define A 1


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  ws2812fx.init();
  ws2812fx.setBrightness(255);
  ws2812fx.setSpeed(300);
  ws2812fx.start();
  pinMode(TRIGGER, INPUT_PULLUP); //set default state to HIGH (5v)
  pinMode(A, INPUT);
}
void breathe() {
  //ws2812fx.setColor(0x007BFF);
  ws2812fx.setMode(FX_MODE_FADE);
}
void strobe() {
  ws2812fx.setMode(FX_MODE_MULTI_STROBE);
  ws2812fx.setColor(0xFFFFFF);
}
void loop() {
//start the service
ws2812fx.service(); 
while (digitalRead(TRIGGER) == HIGH){
  strobe();
}
}
