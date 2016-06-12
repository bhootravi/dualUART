#include <SoftwareSerial.h>
#include "esp.h"

extern SoftwareSerial mySerial; // RX, TX

//1 = ready for processing
//0 = receiving
//????2 = no cmd

extern at_params esp_at_params;
extern at_state esp_at_state;

//long x = 0;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  
  Serial.println("Goodnight moon!");
  // set the data rate for the SoftwareSerial port
  mySerial.begin(19200);
  //mySerial.println("Hello, world?");
  esp_init();
  //esp_at_state.rx_flag = 2;
}

void loop() // run over and over
{
  if (mySerial.available())
  {
    Serial.println("asdas");
    at_get_char();
  }

  //TODO the case when non response data is recived within timeout
  //wait for timeout period for response
  at_timeout();
  
  if (Serial.available())
    mySerial.write(Serial.read());
  
  //process recieved response
  if(esp_at_state.rx_flag == 1)
  {
    esp_at_state.rx_flag = 2;
  }
  /*
  if(rx_flag == 1)
  {
    rx_flag = 2;
  }
  */
}

