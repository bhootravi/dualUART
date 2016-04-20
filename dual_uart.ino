/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.

 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

//time(in ms) to wait for the response before processing
int res_timeout = 2000;

//1 = ready for processing
//0 = receiving
//????2 = no cmd
char rx_flag = 2;

#define pos_at_del '@'
#define pos_end_del '&'

#define eol "\r\n"
#define eol_len 2

char res[1000] = {0};
int i = 0;
char pos[100] = {0};
int deli = 0;
int eolpos[10] = {0};
int dd = 0;
char* dels = "+:'\"";
char* t = dels;
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
    Serial.println("asdas");
    //initialise related variables and goto receiving state
    if(rx_flag == 2)
    {
      rx_flag = 0;
      for(int j = 0; j < 1000; j++)
      {
        res[j] = 0;
        pos[j/10] = 0;
        eolpos[j/100] = 0;
      }
      i = 0;
      deli = 0;
      dd = 0;
      x = millis();
    }
    
    //slow processing case
    if(rx_flag == 1)
      Serial.println("Do something about this");
      //use secondary buffer
    
    //receiving state - store available byte in buffer
    //TODO the case when non response data is recived within timeout
    if(rx_flag == 0)
    {
      while (mySerial.available())
      {
        res[i] = (mySerial.read());
        
        if(res[i] == eol[eol_len-1])
        {
          char ff = 1;
          for(int j = 1; j < eol_len; j++)
          {
            if(res[i-j] != eol[eol_len-1-j])
              ff = 0;
          }
          if(ff == 1)
          {
            eolpos[dd++] = (i-eol_len+1);
          }
        }
        
        t = dels;
        while(*t)
        {
          if(res[i] == *t)
          {
            int j = i;
            //Serial.println(*t);
            pos[deli++] = res[j];
            pos[deli++] = pos_at_del;
            sprintf(&pos[deli], "%d", j);
            int n = 1;
            
            //if (j >= 100000000){j /= 100000000; n += 8;}
            //if (j >= 10000){j /= 10000; n += 4;}
            if (j >= 100){j /= 100; n += 2;}
            if (j >= 10){j /= 10; n += 1;}
            deli += n;
            pos[deli++] = pos_end_del;
          }
          t++;
        }
        i++;
      }
    }
  }
  //wait for timeout period for response
  
  if((rx_flag == 0) && ((millis() - x) > res_timeout))
  {
      rx_flag = 1;
      /*
      for(int j = 0; j < i; j++)
      {
        t = dels;
        while(*t)
        {
          if(res[j] == *t)
          {
            //Serial.println(*t);
            pos[deli++] = res[j];
            pos[deli++] = pos_at_del;
            sprintf(&pos[deli], "%d", j);
            int n = 1;
            k = j;
            //if (k >= 100000000){k /= 100000000; n += 8;}
            //if (k >= 10000){k /= 10000; n += 4;}
            if (k >= 100){k /= 100; n += 2;}
            if (k >= 10){k /= 10; n += 1;}
            deli += n;
            pos[deli] = pos_end_del;
          }
          t++;
        }
      }
      */
      Serial.print("i = ");
      Serial.println((int)i);
      Serial.println(res);
      
      Serial.println(pos);
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

