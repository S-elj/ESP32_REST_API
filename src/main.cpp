#include <TFT_eSPI.h>

#include "ESPAsyncWebServer.h"

#include "WiFi_utils.h"
#include "Routes.h"

AsyncWebServer server(80);

void setup() {
  Serial.begin(MONITOR_SPEED);

  // Connexion au WiFi avec `WiFi_utils`
  setup_wifi();
  // Montage du système de fichiers SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("Erreur lors du montage du système de fichiers SPIFFS !");
    return;
  }
  // Mise en place des pins
  pinMode(36, INPUT);

  server.on("/openapi.yml", HTTP_GET, routes::oapi::handle_oapi_schema);
  server.on("/scalar", HTTP_GET, routes::oapi::handle_scalar);

  server.on("/v1/metadata", HTTP_GET, routes::monitoring::handle_root);

  server.on("/v1/sensors/photocell", HTTP_GET, routes::sensors::handle_photocell_sensor);

  server.begin();
}

void loop() {
  // No-op
}
