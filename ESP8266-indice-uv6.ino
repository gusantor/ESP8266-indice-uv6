#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>

#include <Time.h>
#include <TimeAlarms.h>

#include <ESP8266HTTPClient.h>

#include "uvi_vars.h"

///////vars///////

int actCycle = 0;
int maxCycle = 20;

String AP_NameString;
const char *AP_Password = "adminadmin";

const char *ssid = "";
const char *password = "";

char bufssid[64];
char bufsspass[64];

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

String uviPayload;
String remoteUVI="0";
String remoteFechaMax="";
String remoteFechaUlt="";
String remoteUVIMx="0";
String localUVI="0";
//String localFechaMax="";
String localFechaUlt="";
String tipo;

unsigned int localPort = 2390;      // local port to listen for UDP packets

/* Don't hardwire the IP address or we won't get the benefits of the pool.
 *  Lookup the IP address for the host name instead */
//IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server
IPAddress timeServerIP; // time.nist.gov NTP server address
const char* ntpServerName = "time.nist.gov";

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;
const int timeZone = -3;     // Ch
String formatedDate;

///////////////////////////
struct Location {
  char addr[100];
};
Location default_location = {0};
Location stored_location = {0};

struct Credential {
  char uname[20];
  char upass[50];
};
String defaultUserName="admin";
String defaultUserPass="admin";
Credential default_credential = {0,0};
Credential stored_credential = {0,0};

struct Estacion {
  char id[20];
  char nombre[100];
};
Estacion stored_estacion = {0,0};

struct Display {
  char dmode[50];
  char dpriority[50];
};
char default_dmode = {'Solo local'};
char default_dpriority = {'Principal local - secundario remoto'};

Display stored_display = {0,0};

int defaultPort = 8089;
int port = defaultPort;

///////vars///////

ESP8266WebServer server(port);

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  delay(10);

  Serial.println();
  Serial.println("Inicio");

  mientrasConecta();
  
  //WiFi.disconnect(true);
  //WiFi.mode(WIFI_AP_STA);

  lee_credenciales();
  lee_ubicacion();
  lee_estacion();
  lee_display();

  Alarm.timerRepeat(300, lee_uvi_estacion);
  lee_uvi_estacion();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi connected");
    Serial.print("STA IP address: "); Serial.print(WiFi.localIP());Serial.print(":");Serial.println(port);
  }else{
    Serial.print("Configuring access point...");
    configureAP();
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");Serial.print(myIP);Serial.print(":");Serial.println(port);
  }

  server.on("/", handleRoot);
  server.on("/indice-uv", handleAcercaDeIndiceUV);
  server.on("/ubicacion", handleUbicacion);
  server.on("/obtiene-uvi",handleJSON);

  server.on("/change-to-sta", handleSta);
  server.on("/kill-sta", handleKillSta);
  server.on("/configuracion/kill-sta", handleKillSta2);
  server.on("/configuracion/kill-sta2", handleKillSta3);
  server.on("/configuracion/kill-ap", handleKillAP);

  server.on("/login", handleLogin);
  server.on("/configuracion/estado", handleAppStatus);
  server.on("/configuracion", handleConfiguracion);
  server.on("/configuracion/formulario-admin",handleAdminForm);
  server.on("/configuracion/coneccion-ap", handleSetStation);

  server.on("/configuracion/set-ubicacion", handleSetLocation);
  server.on("/configuracion/set-estacion", handleSetEstacion);
  server.on("/configuracion/set-display", handleSetDisplay);

  server.on("/css/esp8266-pezGordo.css",handleCss);
  server.on("/scripts/general.js",handleJSGeneral);
  server.on("/scripts/inicio.js",handleJSInicio);
  server.on("/scripts/admin.js",handleJSAdmin);
  server.on("/scripts/redirect.js",handleJSRedirect);
  server.on("/scripts/kill-sta.js",handleJSKillSta);
  server.on("/scripts/kill-sta2.js",handleJSKillSta2);

  server.onNotFound(handleNotFound);

  //here the list of headers to be recorded
  const char * headerkeys[] = {"User-Agent","Cookie"} ;
  size_t headerkeyssize = sizeof(headerkeys)/sizeof(char*);
  //ask server to track these headers
  server.collectHeaders(headerkeys, headerkeyssize );
  
  server.begin();
  
  setSyncInterval(60);
  setSyncProvider(haceUDP);
}

void loop() {
  server.handleClient();

  if (stringComplete) {
    //Serial.println(inputString);
    inputString.replace("\n","");
    inputString.replace("\r","");
    if(inputString=="solIP|"){
      envia_data();
    }
    //if(inputString=="solIUVR|"){
    if(tipo=="solIUVR"){
      envia_indice_remoto();
      //Serial.print("indice local ");Serial.println(localUVI);
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
  }

  serialEvent();

  Alarm.delay(0);
}
