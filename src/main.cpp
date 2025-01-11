#include <TFT_eSPI.h>

#include "ESPAsyncWebServer.h"

#include "Buzzer.h"
#include "Led.h"
#include "Routes.h"
#include "WiFi_utils.h"

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
  pinMode(PHOTOCELL_PIN, INPUT);
  pinMode(THERMISTOR_PIN, INPUT);

  server.on("/openapi.yml", HTTP_GET, routes::oapi::handle_oapi_schema);
  server.on("/scalar", HTTP_GET, routes::oapi::handle_scalar);
  server.on("/v1/metadata", HTTP_GET, routes::monitoring::handle_root);

  server.on("/v1/sensors/photocell", HTTP_GET,
            routes::sensors::handle_photocell_sensor);
  server.on("/v1/minuteur/activate", HTTP_POST,
            routes::mechanical::handle_buzzer_activate);
  server.on("/v1/minuteur/stop", HTTP_POST,
            routes::mechanical::handle_buzzer_stop);
  server.on("/v1/minuteur/activate", HTTP_POST,
            routes::mechanical::handle_buzzer_activate);
  server.on("/v1/minuteur/stop", HTTP_POST,
            routes::mechanical::handle_buzzer_stop);

  server.on("/v1/led/state", HTTP_GET,
            routes::mechanical::handle_led_get_state);
  server.on("/v1/led/automatic", HTTP_POST,
            routes::mechanical::handle_led_set_automatic);
  server.on("/v1/led/luminosity", HTTP_POST,
            routes::mechanical::handle_led_set_luminosity);
  server.on("/v1/led/threshold", HTTP_POST,
            routes::mechanical::handle_led_set_threshold);

  server.begin();
}

void loop() {
  buzzer.loop();
  led.loop();
  delay(100);
}
