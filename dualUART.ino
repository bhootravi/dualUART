#include <SoftwareSerial.h>
#include "esp.h"

SoftwareSerial mySerial(10, 11); // RX, TX

//time(in ms) to wait for the response before processing
int res_timeout = 2000;

//1 = ready for processing
//0 = receiving
//????2 = no cmd
char rx_flag = 2;



//response buffer
char res[1000] = {0};
int i = 0; //index of res
//special char position buffer
//char pos[100] = {0};
//int deli = 0; //index of pos
//EOL position buffer
int eolpos[10] = {0};
int dd = 0; //index of eolpos

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

//clear all the global buffers and their index
void clear_bufs()
{
  for(int j = 0; j < 1000; j++)
  {
    res[j] = 0;
    //pos[j/10] = 0;
    eolpos[j/100] = 0;
  }
  i = 0; 
  //deli = 0;
  dd = 0;
}

//TODO check buffer overflow
//check for special characters at ith index of buf
//append output in global array 'pos' at index 'deli' 
//output string format "(sp.char)pos_at_del(i)pos_end_del"
char check_delimiters(char* buf, int i)
{
  //temp pointer to string of sp. characters
  char* t = dels;
  
  //check each sp. char
  while(*t)
  {
    if(buf[i] == *t)
    {
      return *t;
    }
    //iterate for next sp. char
    t++;
  }
  return -1;
}

//find next eol
int find_eol()
{return -1;}

//TODO check buffer overflow
//Identifies end of multi-char eol at given index
//checks if the EOL "ENDS" at the given index i of buf
//stores the "START" index of EOL in eolpos at index dd
//implicit data:
//#define eol of len #define eol_len
//eolpos(array to store eol index), dd(last index of eolpos)

int check_eol(char* buf, int i)
{
  // flag for the result
  char ff = 0;
  //check if the last char of EOL matches the given index
  if(buf[i] == eol[eol_len-1])
  {
    //possible match
    ff = 1;
    //check the remaining chars backwards
    for(int j = 1; j < eol_len; j++)
    {
      //mismatch of any char with the defined eol
      if(buf[i-j] != eol[eol_len-1-j])
        ff = 0;
    }
    //store the index of "START" of EOL in eolpos
    if(ff == 1)
    {
      eolpos[dd++] = (i-eol_len+1);
    }
  }
  return ff;
}

//checks if the line ending at eolpos[i](i.e. (i+1)th line) ends in
//any of the strings in end_tags
//implicit data:
//end_tags array containing strings that indicate end of response
//returns the index of tag that matched
int check_end_tag(char* buf, int i)
{
  char ff = -1;
  int start_i, end_i, j = 0;
  if((i-1) < 0)
    start_i = 0;
  else
    start_i = eolpos[i-1] + eol_len - 1;
  if(i >= 0)
    end_i = eolpos[i];
  else 
    return -1;
  //Serial.println("check call");
  for(j = 0; j < end_tags_len; j++)
  {
    int x = strlen(end_tags[j]);
    //Serial.println(x);
    //Serial.println(end_tags[j]);
    if(x < (end_i - start_i))
    {
      //Serial.println((char*)&buf[end_i - x]);
      if(strncmp(&buf[end_i - x], end_tags[j], x) == 0)
      {
        ff = 1;
        return j;
      }
    }
  }
  return ff;
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

