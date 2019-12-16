#include "barServer.h"

const char *SSID="BartosLED";
const char *PASS="BartosIMPprojectLED";

const IPAddress localIP(192,168,0,2);
const IPAddress gateway(192,168,0,1);
const IPAddress subnet(255,255,255,0);

ESP8266WebServer server(SERVER_PORT);

void setUpServer(){
  Serial.print("AP configuration was ");
  Serial.println(WiFi.softAPConfig(localIP,gateway,subnet)?"Successful":"Unsuccessful");

  Serial.printf("Connecting to AP '%s' was %s\n",SSID,WiFi.softAP(SSID,PASS)?"Successful":"Unsuccessful");
  delay(500);
  Serial.print("IP address is :");
  Serial.println(WiFi.softAPIP());

  server.on("/",handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();
}

void handleRoot(){
    server.send(200,"text/plain","Root !!!");
    simpleSequence();
}

void handleNotFound(){}