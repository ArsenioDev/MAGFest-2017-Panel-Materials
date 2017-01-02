//Passive activity is breathing LEDs, on trigger or fire cue strobe firing

#include <WS2812FX.h>

#define LED_COUNT 13
#define LED_PIN 11

#define TIMER_MS 5000

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  ws2812fx.init();
  ws2812fx.setBrightness(255);
  ws2812fx.setSpeed(200);
  ws2812fx.setColor(0x007BFF);
  ws2812fx.setMode(FX_MODE_MULTI_STROBE);
  ws2812fx.start();
}

void loop() {
  // put your main code here, to run repeatedly:

}
