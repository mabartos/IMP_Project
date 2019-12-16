#ifndef BARTOS_SERVER
#define BARTOS_SERVER

#define SERVER_PORT 8282
#include <ESP8266WebServer.h>
#include "barLights.h"

extern const char *SSID;
extern const char *PASS;
extern ESP8266WebServer server;

void setUpServer();
void handleRoot();
void handleNotFound();

#endif //BARTOS_SERVER