#include <ESPAsyncWebServer.h>

class Monitoring {
  public:
};
namespace routes {
  namespace monitoring {
    void handle_root(AsyncWebServerRequest *request);
  }
}
