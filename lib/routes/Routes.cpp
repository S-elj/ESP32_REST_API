#include "Routes.h"
#include "AsyncJson.h"
#include "Buzzer.h"
#include "ESPAsyncWebServer.h"
#include "Led.h"
#include "WiFi.h"
#include "esp_log.h"

#define HANDLE_OAPI_VAR(variable)                                              \
  if (var == #variable)                                                        \
    return F(variable);

String oapi_schema_variables_processor(const String &var) {
  HANDLE_OAPI_VAR(PROJECT_NAME);
  HANDLE_OAPI_VAR(PROJECT_DESCRIPTION);
  HANDLE_OAPI_VAR(PROJECT_VERSION);

  if (var == "ADDRESS")
    return F(WiFi.localIP().toString().c_str());

  return String();
}

void routes::oapi::handle_oapi_schema(AsyncWebServerRequest *request) {
  request->send(SPIFFS, "/openapi.yml", "text/yaml", false,
                oapi_schema_variables_processor);
}

void routes::oapi::handle_scalar(AsyncWebServerRequest *request) {
  request->send(SPIFFS, "/index.html", "text/html", false,
                oapi_schema_variables_processor);
}

void routes::monitoring::handle_root(AsyncWebServerRequest *request) {
  AsyncJsonResponse *response = new AsyncJsonResponse();

  JsonVariant &root = response->getRoot();
  root["name"] = String(PROJECT_NAME);
  root["description"] = String(PROJECT_DESCRIPTION);
  root["version"] = String(PROJECT_VERSION);
  root["uptime"] = esp_log_timestamp();

  response->setLength();
  request->send(response);
};

void routes::sensors::handle_photocell_sensor(AsyncWebServerRequest *request) {
  AsyncJsonResponse *response = new AsyncJsonResponse();

  JsonVariant &root = response->getRoot();
  root["name"] = String("photocell");
  root["value"] = analogRead(PHOTOCELL_PIN);

  response->setLength();
  request->send(response);
}

void routes::mechanical::handle_buzzer_activate(
    AsyncWebServerRequest *request) {
  if (!request->hasParam("delay") || !request->hasParam("duration")) {
    AsyncJsonResponse *response = new AsyncJsonResponse();
    JsonVariant &root = response->getRoot();
    root["message"] = "Il manque la duration ou le délai!";
    response->setCode(400);
    response->setLength();
    request->send(response);
    return;
  }

  unsigned long delay = request->getParam("delay")->value().toInt();
  unsigned long duration = request->getParam("duration")->value().toInt();

  AsyncJsonResponse *response = new AsyncJsonResponse();
  JsonVariant &root = response->getRoot();
  root["success"] = !buzzer.is_planned();

  response->setLength();
  request->send(response);

  if (!buzzer.is_planned())
    buzzer.buzz(delay, duration);
}

void routes::mechanical::handle_buzzer_stop(AsyncWebServerRequest *request) {
  buzzer.stop();
  AsyncJsonResponse *response = new AsyncJsonResponse();
  JsonVariant &root = response->getRoot();
  root["success"] = buzzer.is_planned() || buzzer.has_started();
  response->setLength();
  request->send(response);
}

void routes::mechanical::handle_led_get_state(AsyncWebServerRequest *request) {
  AsyncJsonResponse *response = new AsyncJsonResponse();
  JsonVariant &root = response->getRoot();
  root["is_automatic"] = led.is_automatic();
  root["luminosity"] = led.get_luminosity();
  root["threshold"] = led.get_threshold();
  response->setLength();
  request->send(response);
}

void routes::mechanical::handle_led_set_automatic(
    AsyncWebServerRequest *request) {
  if (!request->hasParam("enabled")) {
    AsyncJsonResponse *response = new AsyncJsonResponse();
    JsonVariant &root = response->getRoot();
    root["message"] = "Il faut spécifier la valeur du mode automatique!";
    response->setCode(400);
    response->setLength();
    request->send(response);
    return;
  }

  bool automatic =
      request->getParam("enabled")->value().equalsIgnoreCase("true");

  AsyncJsonResponse *response = new AsyncJsonResponse();
  JsonVariant &root = response->getRoot();
  root["success"] = true;

  response->setLength();
  request->send(response);

  led.set_automatic(automatic);
}

void routes::mechanical::handle_led_set_luminosity(
    AsyncWebServerRequest *request) {
  if (!request->hasParam("value")) {
    AsyncJsonResponse *response = new AsyncJsonResponse();
    JsonVariant &root = response->getRoot();
    root["message"] = "Il faut spécifier la valeur du mode automatique!";
    response->setCode(400);
    response->setLength();
    request->send(response);
    return;
  }

  double value = request->getParam("value")->value().toDouble();

  AsyncJsonResponse *response = new AsyncJsonResponse();
  JsonVariant &root = response->getRoot();
  root["success"] = true;

  response->setLength();
  request->send(response);

  led.set_luminosity(value);
}

void routes::mechanical::handle_led_set_threshold(
    AsyncWebServerRequest *request) {
  if (!request->hasParam("value")) {
    AsyncJsonResponse *response = new AsyncJsonResponse();
    JsonVariant &root = response->getRoot();
    root["message"] = "Il faut spécifier la valeur du threshold!";
    response->setCode(400);
    response->setLength();
    request->send(response);
    return;
  }

  double value = request->getParam("value")->value().toDouble();

  AsyncJsonResponse *response = new AsyncJsonResponse();
  JsonVariant &root = response->getRoot();
  root["success"] = true;

  response->setLength();
  request->send(response);

  led.set_threshold(value);
}
