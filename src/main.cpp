#include <TFT_eSPI.h>

#include "ESPAsyncWebServer.h"

#include "WiFi_utils.h"
#include "Routes.h"

AsyncWebServer server(80);

void setup() {
  Serial.begin(MONITOR_SPEED);

  // Connexion au WiFi avec `WiFi_utils`
  setup_wifi();

  server.on("/", HTTP_GET, routes::monitoring::handle_root);
  server.begin();
}

void loop() {
  // No-op
}
