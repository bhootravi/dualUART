#ifndef AT_H
#define AT_H

#include <Arduino.h>
#include <SoftwareSerial.h>

typedef struct at_params
{
  int timeout;
  char* buf;
  int buf_len;
  const char* eol;
  int eol_len;
  const char** end_tags;
  int end_tags_len;
  const char* dels;
}at_params;

typedef struct at_state
{
  //2 - idle
  //0 - receiving
  //1 - receive complete
  char rx_flag;// = 2;
  int i;// = 0;
  int eolpos[10];// = {0};
  int dd;// = 0; //index of eolpos
  long x;// millis at start of rx
}at_state;

extern at_params* params;
extern at_state* state;

//special char position buffer
//char pos[100] = {0};
//int deli = 0; //index of pos

int at_init(at_params* param, at_state* st);
int at_get_char();
int at_available();
int at_nonblocking_get();
int at_blocking_get();
void at_processing_done();
void at_send_cmd(char* cmd);
void clear_bufs();
void at_timeout();
char check_delimiters(char* buf, int i);
int check_eol(char* buf, int i);
int check_end_tag(char* buf, int i);
int find_eol();

#endif
