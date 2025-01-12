#include <WiFi.h>

/*
 * Ce fichier permet la configuration du WiFi à l'aide des variables
 * d'environnement définies dans le fichier
 * `./config/wifi.ini`.
 *
 * Cette fonction bloque, d'une certaine façon. Elle effectue une vérification
 * toutes les 0.5 secondes pour voir si la connexion est établie.
 */
void setup_wifi();
