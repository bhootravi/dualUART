#include <SoftwareSerial.h>
#include "esp.h"

SoftwareSerial mySerial(10, 11); // RX, TX

//1 = ready for processing
//0 = receiving
//????2 = no cmd
extern char rx_flag;

long x = 0;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Goodnight moon!");
  // set the data rate for the SoftwareSerial port
  mySerial.begin(19200);
  //mySerial.println("Hello, world?");

  rx_flag = 2;
}

void loop() // run over and over
{
  if (mySerial.available())
  {
    //Serial.println("asdas");
    //initialise related variables and goto receiving state
    if(rx_flag == 2)
    {
      rx_flag = 0;
      clear_bufs();
      x = millis();
    }
    
    //slow processing case
    if(rx_flag == 1)
      Serial.println("Do something about this");
      //use secondary buffer
    //receiving state - store available byte in buffer
    if(rx_flag == 0)
    {
      while (mySerial.available())
      {
        res[i] = (mySerial.read());
        if(check_eol(res, i))
        {
          Serial.print("found eol at ");
          Serial.println(eolpos[dd-1]);
          int xx = check_end_tag(res, dd - 1);
          if(xx >= 0)
          {
            Serial.println("tag foung");
            Serial.println(end_tags[xx]);
          }
        }
        //check_delimiters(res, i);
        i++;
      }
    }
  }

  //TODO the case when non response data is recived within timeout
  //wait for timeout period for response
  if((rx_flag == 0) && ((millis() - x) > res_timeout))
  {
      rx_flag = 1;
      
      Serial.print("i = ");
      Serial.println((int)i);
      Serial.println(res);
      
      //Serial.println(pos);
      Serial.println();
      
      for(int j = 0; j < 10; j++)
      {
        Serial.print((int)eolpos[j]);
        Serial.print(',');
      }
      Serial.println();
  }
  
  if (Serial.available())
    mySerial.write(Serial.read());

  //process recieved response
  if(rx_flag == 1)
  {
    rx_flag = 2;
  }
}

