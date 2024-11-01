#include <WiFi.h>

String get_wifi_status(int status) {
    switch(status) {
        case WL_IDLE_STATUS:
            return "En attente";
        case WL_SCAN_COMPLETED:
            return "Scan terminé";
        case WL_NO_SSID_AVAIL:
            return "Recherche...";
        case WL_CONNECT_FAILED:
            return "Echec de la connexion";
        case WL_CONNECTION_LOST:
            return "Connexion perdue !";
        case WL_CONNECTED:
            return "Connecté";
        case WL_DISCONNECTED:
            return "Déconnecté";
        default:
            return "Statut inconnu";
    }
}

void setup_wifi() {
    Serial.println("[WiFi_utils] Connexion au Wi-Fi '" + String(WIFI_SSID) + "'");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    int status = WL_IDLE_STATUS;
    while(status != WL_CONNECTED) {
        delay(500);
        status = WiFi.status();
        Serial.println("[WiFi_utils] " + String(get_wifi_status(status)));
    }
    Serial.println("[WiFi_utils] Le WiFi est connecté (adresse locale: " + WiFi.localIP().toString() + ")!");
}
