#include "Arduino.h"
#include "Esp8266\espManager.h"
#include "Led\led.h"
#include <FlexiTimer2.h>

void ledManager();

void setup()
{
pinMode(13,OUTPUT);
initLed();
FlexiTimer2::set(10, ledManager); // 500ms period
FlexiTimer2::start();
  setupEsp();

}

void loop()
{

  listen();

//getTime();
// delay(2000);

}

void ledManager()
{
  rainbowEffect();
}
