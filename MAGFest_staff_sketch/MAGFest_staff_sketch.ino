/*Wizard staff code for MAGFest 2017 panel
Written by Arsenio Dev
Used in "Lights, Motion, Sound: Adding programmability to cosplay with Arduino"
* ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Arsenio Dev wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. 
 * ----------------------------------------------------------------------------
 */

//Passive activity is breathing LEDs, on trigger or fire cue strobe firing

#include <WS2812FX.h>
#include <DFPlayer_Mini_Mp3.h>
#include <SoftwareSerial.h>
#define LED_COUNT 5
#define LED_PIN 8
#define TRIGGER 2

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
bool oldState = HIGH;
int showType = 0;

void setup() {
  // put your setup code here, to run once:
  ws2812fx.init();
  ws2812fx.setBrightness(255);
  ws2812fx.setColor(0xFFFFFF);
  ws2812fx.setMode(FX_MODE_BREATH);
  ws2812fx.start();
  pinMode(TRIGGER, INPUT_PULLUP);
  mp3_set_serial (Serial); //set Serial for DFPlayer-mini mp3 module 
  mp3_set_volume (10);
}

void loop() {
ws2812fx.service();

 // Get current button state.
digitalRead(TRIGGER);
 bool newState = digitalRead(TRIGGER);

  // Check if state changed from high to low (button press).
  if (newState == LOW && oldState == HIGH) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(TRIGGER);
    if (newState == LOW) {
     showType++;
      if (showType > 1)
        showType=0;
      startShow(showType);
    }
  }
   // Set the last button state to the old state.
  oldState = newState;
}

void startShow(int i) {
  switch(i){
    case 0: ws2812fx.setMode(FX_MODE_BREATH);
            mp3_play (1); //play 0001.mp3
            break;
    case 1: ws2812fx.setMode(FX_MODE_MULTI_STROBE);
            mp3_play (2); 
            break;

  }
}
