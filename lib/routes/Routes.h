#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>
#include <SPIFFS.h>

namespace routes {
  namespace oapi {
    // Renvoie le schéma OpenAPI de l'API pour le projet, disponible dans le dossier `/data/openapi.yml`.
    // Il faut noter que certains paramètres de l'API sont inclus dynamiquement (notamment la version, cf. implémentation).
    void handle_oapi_schema(AsyncWebServerRequest *request);
    
    // Renvoie une interface graphique à l'aide de [Scalar](https://scalar.vector.dev/).
    void handle_scalar(AsyncWebServerRequest *request);
  }
  namespace monitoring {
    // Gère la route `/v1/` comme définie dans le schéma OAPI.
    void handle_root(AsyncWebServerRequest *request);
  }
  namespace sensors {
    // Renvoie les métadonnées à propos du photocell, généralement placé au pin 36.
    void handle_photocell_sensor(AsyncWebServerRequest *request);
  }
  namespace mechanical {
    void handle_buzzer_stop(AsyncWebServerRequest *request);
    void handle_buzzer_activate(AsyncWebServerRequest *request);
    void handle_led_get_state(AsyncWebServerRequest *request);
    void handle_led_set_automatic(AsyncWebServerRequest *request);
    void handle_led_set_luminosity(AsyncWebServerRequest *request);
  }
}
