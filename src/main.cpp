#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <barLights.h>
#include <barServer.h>

void setup() {
  Serial.begin(115200);
  setUpServer();
  setUpLights();
}

void loop() {
  server.handleClient();
  delay(10);
}