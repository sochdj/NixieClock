#include "data.h"


CRGBPalette16 currentPalette=RainbowColors_p;
TBlendType    currentBlending=LINEARBLEND;
bool on=false;

CRGBPalette16 getPalette(){
  return currentPalette;
}
TBlendType getBlending(){
  return currentBlending;
}
void setPalette(CRGBPalette16 palette){
  currentPalette=palette;
}
void setBlending(TBlendType blend){
  blend=currentBlending;
}

void setLedState(bool state){
  on=state;
}
bool getLedState()
{
  return on;
}
