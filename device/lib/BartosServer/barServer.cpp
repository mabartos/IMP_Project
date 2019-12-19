#include "barServer.h"

const char *SSID="BartosLED";
const char *PASS="BartosIMPprojectLED";

const char *SSID_TEST="Bejvak";
const char *PASS_TEST="B3jv4k.4Man";

bool isFading=false;
bool isBlicking=false;

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

  server.on("/blicking",handleBlicking);
  server.on("/fading",handleFading);

  server.on("/red",handleRed);
  server.on("/green",handleGreen);
  server.on("/blue",handleBlue);

  server.onNotFound(handleNotFound);
  server.begin();
}


void handleBlicking(){
  if(server.args()>0 && server.arg("state")!=""){
      if(server.arg("state")=="on"){
        isBlicking=true;
        isFading=false;
        server.send(200,"text/plain","Blicking is turned ON.");
        return;
      }else if(server.arg("state")=="off"){
        isBlicking=false;
        server.send(200,"text/plain","Blicking is turned OFF.");
        return;
      }
  }
  server.send(400,"text/plain","Error! State have to be either ON or OFF!");
}

void handleFading(){
  if(server.args()>0 && server.arg("state")!=""){
      if(server.arg("state")=="on"){
        isFading=true;
        isBlicking=false;
        server.send(200,"text/plain","Fading is turned ON.");
        return;
      }else if(server.arg("state")=="off"){
        isFading=false;
        server.send(200,"text/plain","Fading is turned OFF.");
        return;
      }
  }
  server.send(400,"text/plain","Error! State have to be either ON or OFF!");
}

void handleGeneral(char *message,uint16_t pin){
  Serial.println("Fading:");
  Serial.println(isFading);
  Serial.println("Blicking:");
  Serial.println(isBlicking);
  Serial.println("........:");

  if(server.args()>0 && server.arg("state")=="on"){
    if(isBlicking){
      blickingIteration(pin,COUNT_OF_ITERATIONS);
      server.send(200,"text/plain",message);
      return;
    }else if(isFading){
      fadingIteration(pin,1);
      server.send(200,"text/plain",message);
      return;
    }
  }
    handleGeneralState(pin);
    server.send(200,"text/plain",message);
}

void handleGeneralIntensity(char *message,uint16_t pin){
  if(server.args()>0 && server.arg("intensity")!=""){
      uint8_t intensity=strtol(server.arg("intensity").c_str(),NULL,10);
      if(changeIntensity(pin,intensity)){
        server.send(200,"text/plain",message);
        return;
      }
  }
  server.send(400,"text/plain","Error! Intensity of the device has to be in range 0-100 and turned ON.");
}

void handleGeneralState(uint16_t pin){
  if(server.args()>0){
      if(server.arg("state")=="on"){
        digitalWrite(pin,HIGH);
        server.send(200,"text/plain","State of the device is ON.");
        return;
      }else if(server.arg("state")=="off"){
        digitalWrite(pin,LOW);
        server.send(200,"text/plain","State of the device is OFF.");
        return;
      }
      server.send(400,"text/plain","Error! State have to be either ON or OFF!");
  }else{
    digitalWrite(pin,!digitalRead(pin));
    server.send(200,"text/plain","State of the device is ON.");
  }
}

void handleRoot(){
    server.send(200,"text/plain","Root !!!");
    simpleSequence();
}


void handleNotFound(){

}

void handleParseArgs(uint16_t pin){
  if(server.arg("intensity")!=""){
    handleGeneralIntensity("Intensity of LED was changed.",pin);
  }else{
    handleGeneral("State of LED was changed",pin);
  }
}

void handleRed(){
  handleParseArgs(RED_LED);
}

void handleGreen(){
  handleParseArgs(GREEN_LED);
}

void handleBlue(){
  handleParseArgs(BLUE_LED);
}
