#include <WiFi.h>
#include <TFT_eSPI.h>
#include <ESPAsyncWebServer.h>
#include <WiFi_utils.h>

AsyncWebServer server(80);

void setup() {
  Serial.begin(ENV_MONITOR_SPEED);

  // Connexion au WiFi avec `WiFi_utils`
  setup_wifi();

  server.begin();
}

void loop() {
  // No-op
}
