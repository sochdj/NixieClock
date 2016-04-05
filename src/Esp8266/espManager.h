#include "Arduino.h"
#include <SoftwareSerial.h>
#include <Time.h>
#include <Timezone.h>
#include "../data.h"

#define Esp8266 Serial2
#define DEBUG true




void setupEsp() ;
String sendData(String command, const int timeout, boolean debug);
void listen();


boolean cwJoinAP();
boolean waitOKfromESP8266(int timeout);
void getTime() ;
void clearESP8266SerialBuffer();
byte wait_for_esp_response(int timeout, char* term);
