#include <WiFi.h>
#include <TFT_eSPI.h>
#include <ESPAsyncWebServer.h>

const char* ssid     = "shreb";
const char* password = "kooookkk";

TFT_eSPI tft = TFT_eSPI();
AsyncWebServer server(80);

String get_wifi_status(int status) {
    switch(status) {
        case WL_IDLE_STATUS:
            return "WiFi: En attente";
        case WL_SCAN_COMPLETED:
            return "WiFi: Scan terminé";
        case WL_NO_SSID_AVAIL:
            return "WiFi: Recherche...";
        case WL_CONNECT_FAILED:
            return "WiFI: Echec de la connexion";
        case WL_CONNECTION_LOST:
            return "WiFi: Connexion perdue !";
        case WL_CONNECTED:
            return "WiFi: Connecté";
        case WL_DISCONNECTED:
            return "WiFi: Déconnecté";
        default:
            return "WiFi: Statut inconnu";
    }
}

void setup() {
    tft.init();
    // Connexion au WIFI
    Serial.begin(115200);
    Serial.println("[WiFi] Connexion au Wi-Fi");
    WiFi.begin(ssid, password);
    int status = WL_IDLE_STATUS;
    while(status != WL_CONNECTED) {
        delay(500);
        status = WiFi.status();
        Serial.println(get_wifi_status(status));
    }

    tft.setRotation(1);         // Rotation de l'affichage si nécessaire
    tft.fillScreen(TFT_BLACK);  // Effacer l'écran
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);  // Taille du texte
    tft.setTextDatum(MC_DATUM);
    tft.setCursor(0, 0);
    tft.drawString(WiFi.localIP().toString(), tft.width() / 2, tft.height() / 2);

    // Corriger la syntaxe ici
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) { // *request est un pointeur
        request->send(200, "text/plain", "Hello, world");
    });
    
    server.on("/", HTTP_POST, [](AsyncWebServerRequest *request) { // *request est un pointeur
        if (request->hasParam("message", true)) {
            tft.fillScreen(TFT_BLACK);
            tft.setTextDatum(MC_DATUM);
            tft.setCursor(0, 0);
            tft.drawString(request->getParam("message", true)->value(), tft.width() / 2, tft.height() / 2);
            request->send(200, "text/plain", "Ok");
        } else {
            request->send(200, "text/plain", "Param");
        }
    });

    server.begin();
}

void loop() {}
