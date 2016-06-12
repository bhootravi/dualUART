#include "esp.h"

//time(in ms) to wait for the response before processing
int res_timeout = 2000;
//response buffer
char res[1000] = {0};
//strings that denote end of transmission
const char* end_tags[end_tagsLen] = {"OK", "ERROR", "FAIL", "SEND OK", "CONNECT"};
//special characters used as delimitors
const char* dels = "+:'\"";

at_params esp_at_params;
at_state esp_at_state;
esp_config local_config;

  char echo = 0;
  char sdk[5];
  struct uart_config esp_uart;
  char mode;// = sta_ap;
  char smartconfig;// = 0;
  char sta_dhcp;// = 1;
  char ap_dhcp;

void esp_init()
{
  esp_at_params.timeout = 2000;
  esp_at_params.buf = &res[0];
  esp_at_params.buf_len = 1000;
  esp_at_params.eol = EOL;
  esp_at_params.eol_len = EOL_LEN;
  esp_at_params.end_tags = &end_tags[0];
  esp_at_params.end_tags_len = end_tagsLen;
  esp_at_params.dels = dels;
  at_init(&esp_at_params, &esp_at_state);
  esp_echo(ECHO_OFF);
}

int esp_echo(char in)
{
  int xx;
  if(in == ECHO_OFF)
  {
    at_send_cmd("ATE0");
    xx = at_blocking_get();
    if(xx == OK_ind)
    {
      local_config.echo = ECHO_OFF;
      Serial.println("esp");
      Serial.println(esp_at_params.buf);
      at_processing_done();
      return 0;
    }
  }
  else if(in == ECHO_ON)
  {
    at_send_cmd("ATE1");
    xx = at_blocking_get();
    if(xx == OK_ind)
    {
      local_config.echo = ECHO_ON;
      Serial.println("esp");
      Serial.println(esp_at_params.buf);
      at_processing_done();
      return 0;
    }
  }
  return 1;
}

int esp_mode(char in)
{
  if(in == QUERY)
  {
    at_send_cmd("AT+CWMODE_CUR?");
    xx = at_blocking_get();
    if(xx == OK_ind)
    {
      at_processing_done();
      //local_config.mode = ;
      Serial.println("esp");
      Serial.println(esp_at_params.buf);
      return 0;
    }
  }
}

int connect_ap(esp_ap_connection* ap)
{
  return -1;
}
/*
start_server()
stop_server()

available_ap()
  connect_ap()
disconnect_ap()
set_ip_sta()
set_ip_ap()
set_mac_sta()
set_mac_ap()

create_ap()
config_ap()
stop_ap()

tcp_connect()
tcp_disconnect()
tcp_send()

udp_connect()
udp_disconnect()
udp_send()

esp_ping()
esp_test()
esp_version()
esp_restore()
esp_echo()
*/
