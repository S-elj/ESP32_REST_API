#include "AsyncJson.h"
#include "ESPAsyncWebServer.h"
#include "Routes.h"

namespace routes {
  namespace monitoring {
    void handle_root(AsyncWebServerRequest *request) {
      AsyncJsonResponse * response = new AsyncJsonResponse();
  
      JsonVariant& root = response->getRoot();
      root["name"] = PROJECT_NAME;
      root["description"] = PROJECT_DESCRIPTION;
      root["version"] = PROJECT_VERSION;

      response->setLength();
      request->send(response);
    };
  } 
}
