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

//Passive activity is breathing LEDs, on RED or fire cue strobe firing
#include <Servo.h>
#include <WS2812FX.h>
#include <DFPlayer_Mini_Mp3.h>
#include <SoftwareSerial.h>
#define LED_COUNT 7
#define LED_PIN 6
#define RED 8
#define BLUE 9
#define FLAP 5


SoftwareSerial mySerial(10, 11); //RX. TX
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
bool oldState2 = HIGH;
int showType = 0;

Servo flaps;
int pos = 90;

void setup() {
  // put your setup code here, to run once:
  ws2812fx.init();
  ws2812fx.setBrightness(255);
  ws2812fx.setColor(0xFF5900);
  ws2812fx.setMode(FX_MODE_FADE);
  ws2812fx.start();
  pinMode(RED, INPUT_PULLUP);
  mySerial.begin (9600);
  mp3_set_serial (mySerial);  //set softwareSerial for DFPlayer-mini mp3 module 
  mp3_set_volume (30);
  flaps.attach(FLAP);
}

void loop() {
ws2812fx.service();

 // Get current button state.
digitalRead(RED);
 bool newState = digitalRead(RED);

  // Check if state changed from high to low (button press).
  if (newState == LOW && oldState == HIGH) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(RED);
    if (newState == LOW) {
     showType++;
      if (showType > 1)
        showType=0;
      startShow(showType);
    }
  }
   // Set the last button state to the old state.
  oldState = newState;
  
  // Get current button state. for blue
}

void startShow(int i) {
  switch(i){
    case 0: ws2812fx.setMode(FX_MODE_FADE);
            ws2812fx.setSpeed(210);
            ws2812fx.setColor(0xFF5900);
            mp3_play (1); //play 0001.mp3
            flaps.write(90);
            break;
    case 1: ws2812fx.setMode(FX_MODE_HYPER_SPARKLE);
            ws2812fx.setSpeed(DEFAULT_SPEED);
            ws2812fx.setColor(0xFF4500);
            mp3_play (2); 
            flaps.write(140);
            break;

  }
}
