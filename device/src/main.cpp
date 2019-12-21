/**
 *  Martin Bartos (xbarto96)
 *  Original (Last modified : 21.12.2019)
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <barLights.h>
#include <barServer.h>

void setup() {
  // Set serial baudrate to 115220 Bd
  Serial.begin(115200);

  // Init Server
  setUpServer();

  //Init Lights
  setUpLights();
}

void loop() {
  // Handle client requests
  server.handleClient();
  delay(10);
}