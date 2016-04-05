
#include "FastLED.h"
#include "../data.h"

#define LED_PIN     35
#define NUM_LEDS    2
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB


#define UPDATES_PER_SECOND 100

void initLed();
void gestLed();
void palette();
void setOffAllLED();
