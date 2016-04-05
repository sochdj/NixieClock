#include "Arduino.h"

#include "FastLED.h"


CRGBPalette16 getPalette();
TBlendType getBlending();
void setPalette(CRGBPalette16);
void setBlending(TBlendType);
void setLedState(bool on);
bool getLedState();
