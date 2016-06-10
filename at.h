typedef struct at_params
{
  int timeout;
  char* buf;
  int buf_len;
  const char* eol;
  const int eol_len;
  const char** end_tags;
  const int end_tags_len;
  const char* dels;
}at_params;

typedef struct at_state
{
  char rx_flag;// = 2;
  int i;// = 0;
  int eolpos[10];// = {0};
  int dd;// = 0; //index of eolpos
}at_state;

int at_init(at_params* param);
void clear_bufs();
char check_delimiters(char* buf, int i);
int check_eol(char* buf, int i);
int check_end_tag(char* buf, int i);
int find_eol();
