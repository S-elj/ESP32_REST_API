#include <ESPAsyncWebServer.h>
#include <Routes.h>

namespace routes {
  namespace monitoring {
    void handle_root(AsyncWebServerRequest *request) {
      request->send(200, "text/plain", "Hello les noobs!");
    };
  } 
}
