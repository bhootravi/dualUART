#define pos_at_del '@'
#define pos_end_del '&'

#define eol "\r\n"
#define eol_len 2

//special characters used as delimitors
char* dels = "+:'\"";

#define end_tags_len 5
const char* end_tags[end_tags_len] = {"OK", "ERROR", "FAIL", "SEND OK", "CONNECT"};

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

struct uart_config
{
  int baud_rate = 19200;
  char databits = 8;
  char stopbits = onebit;
  char parity = none;
  char flow_control = disable;
};

struct esp_config
{
  char echo = 0;
  char sdk[5];
  struct uart_config esp_uart;
  char mode = sta_ap;
  char smartconfig = 0;
  char sta_dhcp = 1;
  char ap_dhcp = 1;
};
//char echo = 0;

struct interface
{
  char ip[16];
  char netmask[16];
  char gateway[16];
  char mac[18];
} sta, ap;

struct ap_connection
{
  char ssid[30];
  char pass[65];
} def_ap;

//use to store properties of created ap ignoring rssi
struct ap_prop
{
  char enc;
  char ssid[30];
  char mac[18];
  char chan;
  int rssi = 0;
};

//for storing nodes connected to ap
struct node
{
  char ip[16];
  char mac[18];
};
