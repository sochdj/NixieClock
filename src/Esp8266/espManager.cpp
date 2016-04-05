#include "espManager.h"

//String SSID = "Alice-38803138";
//String PASSWORD = "";
String SSID = "dati";
String PASSWORD = "aababb9995";

const char* host = "time.nist.gov";

void setupEsp() {


  Serial.begin(115200);
  Esp8266.begin(115200); // your esp's baud rate might be different
  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  sendData("AT+CWLAP\r\n",2000,DEBUG); // reset module


  Esp8266.println("AT+GMR");
  clearESP8266SerialBuffer();
  sendData("AT+CWMODE=1\r\n",2000,DEBUG); // configure as access point
  clearESP8266SerialBuffer();
  Esp8266.println("AT+CWQAP");


   clearESP8266SerialBuffer();
if(cwJoinAP())
Serial.println("CWJAP Success");
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80

}


void listen()
{
  if(Esp8266.available()) // check if the esp is sending a message
 {
  Serial.print(Esp8266.readString());

   if(Esp8266.find("+IPD,") || 1)
   {
    delay(1000); // wait for the serial buffer to fill up (read all the serial data)
    // get the connection id so that we can then disconnect
    int connectionId = Esp8266.read()-48; // subtract 48 because the read() function returns
                                          // the ASCII decimal value and 0 (the first decimal number) starts at 48

    Esp8266.find("pin="); // advance cursor to "pin="

    int pinNumber = (Esp8266.read()-48)*10; // get first number i.e. if the pin 13 then the 1st number is 1, then multiply to get 10
    pinNumber += (Esp8266.read()-48); // get second number, i.e. if the pin number is 13 then the 2nd number is 3, then add to the first number
    Serial.print(pinNumber);
    digitalWrite(pinNumber, !digitalRead(pinNumber)); // toggle pin

    // make close command
    String closeCommand = "AT+CIPCLOSE=";
    closeCommand+=connectionId; // append connection id
    closeCommand+="\r\n";

    sendData(closeCommand,1000,DEBUG); // close connection
   }

 }
}

/*
* Name: sendData
* Description: Function used to send data to Serial2.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the Serial2 (if there is a reponse)
*/
String sendData(String command, const int timeout, boolean debug)
{
    String response = "";

    Esp8266.print(command); // send the read character to the Serial2

    long int time = millis();

    while( (time+timeout) > millis())
    {
      while(Esp8266.available())
      {

        // The esp has data so display its output to the serial window
        char c = Esp8266.read(); // read the next character.
        response+=c;
      }
    }

    if(debug)
    {
      Serial.print(response);
    }

    return response;
}
char OKrn[] = "OK\r\n";
#define BUFFER_SIZE 1024
const int timeZone = -4;
char buffer[BUFFER_SIZE],query[48];
void getTime(/* arguments */) {
  int ch_id, packet_len;
  unsigned long t1, t;
  char *pb;
  String TARGET_ID="1";
    String TARGET_TYPE="UDP";
    //String TARGET_ADDR="www.example.com";
    String TARGET_PORT="123";
    String TARGET_ADDR=host;
    //String TARGET_PORT="80";
  String cmd="AT+CIPSTART=" + TARGET_ID;
  cmd += ",\"" + TARGET_TYPE + "\",\"" + TARGET_ADDR + "\"";
  cmd += ","+ TARGET_PORT;

  sendData(cmd+"\r\n",2000,DEBUG);

cmd="AT+CIPSEND=1, ";
Esp8266.print(cmd);
Esp8266.println(sizeof(query));
wait_for_esp_response(1000,OKrn);
Esp8266.write((uint8_t *)query,sizeof(query));
Esp8266.readBytes(buffer,sizeof(query));

unsigned long secsSince1900;
  secsSince1900 = (unsigned long)buffer[40] << 24;
  secsSince1900 |= (unsigned long)buffer[41] << 16;
  secsSince1900 |= (unsigned long)buffer[42] << 8;
  secsSince1900 |= (unsigned long)buffer[43];
  t = secsSince1900 - 2208988800UL + timeZone * 3600;

  Serial.println(t);
  char  timeStr[40];
  sprintf(timeStr,"%d/%d/%d %d:%d:%d\n",month(t),day(t),year(t),hour(t),minute(t),second(t));
  Serial.println(timeStr);
  wait_for_esp_response(1000,OKrn);



  String cmdCIPCLOSE = "AT+CIPCLOSE=" + TARGET_ID;

 sendData(cmdCIPCLOSE+"\r\n",2000,DEBUG);
}

boolean waitOKfromESP8266(int timeout)
{
  do{
    Serial.println("wait OK...");
    delay(1000);
    if(Esp8266.find("OK"))
    {
      return true;
    }

  }while((timeout--)>0);
  return false;
}

boolean cwJoinAP()
{
   String cmd="AT+CWJAP=\"" + SSID + "\",\"" + PASSWORD + "\"";
  Esp8266.println(cmd);
  return waitOKfromESP8266(10);
}


void clearESP8266SerialBuffer()
{
  Serial.println("= clearESP8266SerialBuffer() =");
  while (Esp8266.available() > 0) {
    char a = Esp8266.read();
    Serial.write(a);
  }
  Serial.println("==============================");
}


byte wait_for_esp_response(int timeout, char* term) {
  unsigned long t=millis();
  bool found=false;
  int i=0;
  int len=strlen(term);
  // wait for at most timeout milliseconds
  // or if OK\r\n is found
  while(millis()<t+timeout) {
    if(Serial2.available()) {
      buffer[i++]=Serial2.read();
      if(i>=len) {
        if(strncmp(buffer+i-len, term, len)==0) {
          found=true;
          break;
        }
      }
    }
  }
  buffer[i]=0;
  Serial.print(buffer);
  return found;
}
