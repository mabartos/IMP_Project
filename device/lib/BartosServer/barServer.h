/**
 *  Martin Bartos (xbarto96)
 *  Original (Last modified : 21.12.2019)
 */

#ifndef BARTOS_SERVER
#define BARTOS_SERVER

#define SERVER_PORT 8282
#include <ESP8266WebServer.h>
#include "barLights.h"

extern const char *SSID;
extern const char *PASS;
extern ESP8266WebServer server;

// Main function to set up Server
void setUpServer();

// If '/connect' endpoint is invoked
void handleConnect();

// If '/' endpoint is invoked, or not found
void handleRoot();

// If '/blicking?state={on|off}' endpoint is invoked
void handleBlicking();

// If '/fading?state={on|off}' endpoint is invoked
void handleFading();

// General navigation of requests
void handleGeneral(char *name,uint16_t pin);

// General state changer
void handleGeneralState(uint16_t pin);

// General setting of light intensity
void handleGeneralIntensity(char *message,uint16_t pin);

void handleRed();
void handleGreen();
void handleBlue();

void handleSeq1();
void handleSeq2();
void handleSeq3();

#endif //BARTOS_SERVER