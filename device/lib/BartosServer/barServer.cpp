#include "barServer.h"

const char *SSID="BartosLED";
const char *PASS="BartosIMPprojectLED";

const char *SSID_TEST="Bejvak";
const char *PASS_TEST="B3jv4k.4Man";

using namespace std;

const IPAddress localIP(192,168,0,58);
const IPAddress gateway(192,168,0,1);
const IPAddress subnet(255,255,255,0);

ESP8266WebServer server(SERVER_PORT);

void setUpServer(){
  Serial.print("AP configuration was ");
  //Serial.println(WiFi.softAPConfig(localIP,gateway,subnet)?"Successful":"Unsuccessful");

  //Serial.printf("Connecting to AP '%s' was %s\n",SSID,WiFi.softAP(SSID,PASS)?"Successful":"Unsuccessful");
  delay(500);
  Serial.print("IP address is :");
  //Serial.println(WiFi.softAPIP());
  WiFi.begin(SSID_TEST,PASS_TEST);


  Serial.println(WiFi.localIP());

  server.on("/",handleRoot);

  server.on("/red",handleRed);
  server.on("/red/intensity",handleRedIntensity);

  server.on("/green",handleGreen);
  server.on("/green/intensity",handleGreenIntensity);

  server.on("/blue",handleBlue);
  server.on("/blue/intensity",handleBlueIntensity);

  server.onNotFound(handleNotFound);
  server.begin();
}

void handleGeneral(char *message,uint16_t pin){
  server.send(200,"text/plain",message);
  digitalWrite(pin,!digitalRead(pin));
}

void handleRoot(){
    server.send(200,"text/plain","Root !!!");
    simpleSequence();
}


void handleNotFound(){

}

void handleRed(){
  handleGeneral("State of RED LED was changed",RED_LED);
}

void handleRedIntensity(){

}

void handleGreen(){
  handleGeneral("State of GREEN LED was changed",GREEN_LED);
}

void handleGreenIntensity(){

}

void handleBlue(){
  handleGeneral("State of BLUE LED was changed",BLUE_LED);
}

void handleBlueIntensity(){

}