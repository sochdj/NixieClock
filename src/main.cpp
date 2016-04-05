#include "Arduino.h"
#include "Esp8266\espManager.h"


bool toggle=false;
void setup()
{
  pinMode(11,OUTPUT);
   digitalWrite(11,LOW);

   pinMode(12,OUTPUT);
   digitalWrite(12,LOW);

   pinMode(13,OUTPUT);
   digitalWrite(13,LOW);
   pinMode(35,OUTPUT);
     digitalWrite(35,LOW);

  setupEsp();
}

void loop()
{

  listen();

//getTime();
 delay(2000);

}
