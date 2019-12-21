/**
 *  Martin Bartos (xbarto96)
 *  Original (Last modified : 21.12.2019)
 */

#include "barServer.h"
using namespace std;

// AP credentials
const char *SSID="BartosLED";
const char *PASS="BartosIMPprojectLED";

bool isFading=false;
bool isBlicking=false;
bool isConnected=false;

// Server settings
const IPAddress localIP(192,168,66,66);
const IPAddress gateway(192,168,66,1);
const IPAddress subnet(255,255,255,0);

ESP8266WebServer server(SERVER_PORT);

void setUpServer(){
  Serial.print("AP configuration was ");
  Serial.println(WiFi.softAPConfig(localIP,gateway,subnet)?"Unsuccessful":"Successful");

  Serial.printf("Connecting to AP '%s' was %s\n",SSID,WiFi.softAP(SSID,PASS)?"Successful":"Unsuccessful");
  delay(500);
  Serial.print("IP address is :");
  Serial.println(WiFi.softAPIP());

  server.on("/",handleRoot);
  server.on("/connect",handleConnect);

  server.on("/blicking",handleBlicking);
  server.on("/fading",handleFading);

  server.on("/red",handleRed);
  server.on("/green",handleGreen);
  server.on("/blue",handleBlue);

  server.on("/seq1",handleSeq1);
  server.on("/seq2",handleSeq2);
  server.on("/seq3",handleSeq3);

  server.onNotFound(handleRoot);
  server.begin();
}

void handleConnect(){
  if(isConnected){
    server.send(200,"text/plain","Connection to server was Successful");
  }else{
    server.send(400,"text/plain","Connection to server was UNsuccessful");
  }
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
    server.send(200,"text/plain",
    "Available endpoints:\n /red?state={on|off} \n /green?state={on|off} \n /blue?state={on|off} \n /red?intensity={0..100} \n ... !!!");
}

// Parser for requests
void handleParseArgs(uint16_t pin){
  if(server.arg("intensity")!=""){
    handleGeneralIntensity("Intensity of LED was changed.",pin);
  }else{
    handleGeneral("State of LED was changed",pin);
  }
}

// If '/red...' endpoint is invoked 
void handleRed(){
  handleParseArgs(RED_LED);
}

// If '/green...' endpoint is invoked 
void handleGreen(){
  handleParseArgs(GREEN_LED);
}

// If '/blue...' endpoint is invoked 
void handleBlue(){
  handleParseArgs(BLUE_LED);
}

// If '/seq1' endpoint is invoked 
void handleSeq1(){
  sequence1();
  server.send(200,"text/plain","Sequence 1 executing...");
}

// If '/seq2' endpoint is invoked 
void handleSeq2(){
  sequence2();
  server.send(200,"text/plain","Sequence 2 executing...");
}

// If '/seq3' endpoint is invoked 
void handleSeq3(){
  sequence3();
  server.send(200,"text/plain","Sequence 3 executing...");
}
