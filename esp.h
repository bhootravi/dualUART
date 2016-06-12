#ifndef ESP_H
#define ESP_H

#include "at.h"

#define EOL "\r\n"
#define EOL_LEN 2

#define OK_ind  0
#define ERROR_ind  1

#define end_tagsLen 5

#define pos_at_del '@'
#define pos_end_del '&'

#define ECHO_OFF 0
#define ECHO_ON  1

#define QUERY -4

enum parity
{
  none,
  odd,
  even
};

enum stop_bits
{
  onebit,
  onehalfbit,
  twobits
};

enum flow_control
{
  disable,
  RTS,
  CTS,
  RTSandCTS
};

enum wifi_mode
{
  station = 1,
  access_point = 2,
  sta_ap = 3
};

enum ap_encoding
{
  open_wifi,
  wep,
  wpa_psk,
  wpa2_psk,
  wpa_wpa2_psk
};

enum smart_config
{
  disabled,
  esp_touch,
  air_kiss
};

typedef struct uart_config
{
  int baud_rate = 19200;
  char databits = 8;
  char stopbits = onebit;
  char parity = none;
  char flow_control = disable;
}uart_config;

typedef struct esp_config
{
  char echo = 0;
  char sdk[5];
  struct uart_config esp_uart;
  char mode;// = sta_ap;
  char smartconfig;// = 0;
  char sta_dhcp;// = 1;
  char ap_dhcp;// = 1;
}esp_config;
//char echo = 0;

typedef struct esp_interface
{
  char ip[16];
  char netmask[16];
  char gateway[16];
  char mac[18];
}esp_interface;

typedef struct esp_ap_connection
{
  char ssid[30];
  char pass[65];
}esp_ap_connection;

//use to store properties of created ap ignoring rssi
typedef struct esp_ap_prop
{
  char enc;
  char ssid[30];
  char mac[18];
  char chan;
  int rssi = 0;
}esp_ap_prop;

//for storing nodes connected to ap
typedef struct node
{
  char ip[16];
  char mac[18];
};

void esp_init();
int esp_echo(char in);

#endif
