const char* ssid     = "ale";
const char* password = "password";
const char* hostname = "ESP8266_1";

IPAddress ip(192, 168, 1, 200);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// Pines
int pinD = D0;
int pinI = D1;

// Intervalos para velocidades
int velocidades = 25;
int intervalos = int(1000/velocidades);

// Variables de control de tiempo
unsigned long times = 0, flag = 0;
int velocidadD = 13, velocidadI = 13;