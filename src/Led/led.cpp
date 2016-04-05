
#include "led.h"


CRGB strip[NUM_LEDS];


void initLed(){
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(strip, NUM_LEDS).setCorrection( TypicalLEDStrip );
   FastLED.setBrightness(  BRIGHTNESS );

}


void rainbowEffect(){
  uint8_t brightness = 255;
  static uint8_t colorIndex = 0;
      colorIndex = colorIndex + 1; /* motion speed */

  for( int i = 0; i < NUM_LEDS; i++) {
         strip[i] = ColorFromPalette( RainbowColors_p, colorIndex, brightness, LINEARBLEND);
         colorIndex += 3;
     }
  FastLED.show();
  
}
