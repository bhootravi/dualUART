#ifndef AT_H
#define AT_H

typedef struct at_params
{
  int timeout;
  char* buf;
  int buf_len;
  char* eol;
  int eol_len;
  char** end_tags;
  int end_tags_len;
  char* dels;
}at_params;

typedef struct at_state
{
  char rx_flag;// = 2;
  int i;// = 0;
  int eolpos[10];// = {0};
  int dd;// = 0; //index of eolpos
}at_state;

at_params* params;
at_state state;

//special char position buffer
//char pos[100] = {0};
//int deli = 0; //index of pos

int at_init(at_params* param);
void clear_bufs();
char check_delimiters(char* buf, int i);
int check_eol(char* buf, int i);
int check_end_tag(char* buf, int i);
int find_eol();

#endif
