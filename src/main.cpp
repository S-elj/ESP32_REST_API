#include <TFT_eSPI.h> // Inclure la bibliothèque TFT_eSPI

// Initialisation de l'écran
TFT_eSPI tft = TFT_eSPI(); 

void setup() {
  tft.init();              // Initialisation de l'écran
  tft.setRotation(1);      // Définir la rotation de l'affichage (peut varier selon votre écran)
  tft.fillScreen(TFT_BLACK); // Effacer l'écran avec la couleur noire

  tft.setTextColor(TFT_WHITE); // Définir la couleur du texte en blanc
  tft.setTextSize(2);          // Définir la taille du texte
  tft.setCursor(10, 10);       // Définir la position du curseur (x, y)
  
  tft.drawString("Hello World", 10, 10); // Afficher "Hello World"
}

void loop() {
  // Pas besoin de code dans la boucle principale pour cet exemple
}
