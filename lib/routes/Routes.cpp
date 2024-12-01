#include "AsyncJson.h"
#include "ESPAsyncWebServer.h"
#include "WiFi.h"
#include "esp_log.h"
#include "Routes.h"

#define HANDLE_OAPI_VAR(variable) if (var == #variable) return F(variable);

String oapi_schema_variables_processor(const String& var) {
  HANDLE_OAPI_VAR(PROJECT_NAME);
  HANDLE_OAPI_VAR(PROJECT_DESCRIPTION);
  HANDLE_OAPI_VAR(PROJECT_VERSION);

  if (var == "ADDRESS") return F(WiFi.localIP().toString().c_str());
  
  return String();
}

namespace routes {
  namespace oapi {
    void handle_oapi_schema(AsyncWebServerRequest *request) {
      request->send(SPIFFS, "/openapi.yml", "text/yaml", false, oapi_schema_variables_processor);
    }

    void handle_scalar(AsyncWebServerRequest *request) {
      request->send(SPIFFS, "/index.html", "text/html", false, oapi_schema_variables_processor);
    }
  }
  namespace monitoring {
    void handle_root(AsyncWebServerRequest *request) {
      AsyncJsonResponse * response = new AsyncJsonResponse();
  
      JsonVariant& root = response->getRoot();
      root["name"] = String(PROJECT_NAME);
      root["description"] = String(PROJECT_DESCRIPTION);
      root["version"] = String(PROJECT_VERSION);
      root["uptime"] = esp_log_timestamp();

      response->setLength();
      request->send(response);
    };
  } 
}

void routes::sensors::handle_photocell_sensor(AsyncWebServerRequest *request) {
  AsyncJsonResponse * response = new AsyncJsonResponse();

  JsonVariant& root = response->getRoot();
  root["name"] = String("photocell");
  root["value"] = analogRead(36);

  response->setLength();
  request->send(response);
}
