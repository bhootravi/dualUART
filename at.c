#include "at.h"

int at_init(at_params* param)
{
  params = param;
  state.rx_flag = 2;
  state.i = 0;
  state.dd = 0; //index of eolpos
}

//clear all the global buffers and their index
void clear_bufs()
{
  int j;
  for(j = 0; j < 1000; j++)
  {
    params->buf[j] = 0;
    //pos[j/10] = 0;
    state.eolpos[j/100] = 0;
  }
  state.i = 0; 
  //deli = 0;
  state.dd = 0;
}

//TODO check buffer overflow
//check for special characters at ith index of buf
//
  //append output in global array 'pos' at index 'deli' 
  //output string format "(sp.char)pos_at_del(i)pos_end_del"

char check_delimiters(char* buf, int i)
{
  //temp pointer to string of sp. characters
  char* t = params->dels;
  
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
  if(buf[i] == params->eol[params->eol_len-1])
  {
    //possible match
    ff = 1;
    //check the remaining chars backwards
    int j;
    for(j = 1; j < params->eol_len; j++)
    {
      //mismatch of any char with the defined eol
      if(buf[i-j] != params->eol[params->eol_len-1-j])
        ff = 0;
    }
    //store the index of "START" of EOL in eolpos
    if(ff == 1)
    {
      state.eolpos[state.dd++] = (i-params->eol_len+1);
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
    start_i = state.eolpos[i-1] + params->eol_len - 1;
  if(i >= 0)
    end_i = state.eolpos[i];
  else 
    return -1;
  //Serial.println("check call");
  for(j = 0; j < params->end_tags_len; j++)
  {
    int x = strlen(params->end_tags[j]);
    //Serial.println(x);
    //Serial.println(params->end_tags[j]);
    if(x < (end_i - start_i))
    {
      //Serial.println((char*)&buf[end_i - x]);
      if(strncmp(&buf[end_i - x], params->end_tags[j], x) == 0)
      {
        ff = 1;
        return j;
      }
    }
  }
  return ff;
}

//find next eol
int find_eol()
{return -1;}

