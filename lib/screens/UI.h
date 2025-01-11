#ifndef UI_H
#define UI_H

#include <SPI.h>
#include <TFT_eSPI.h>

enum Screen { BUZZER_SCREEN, LED_SCREEN, SENSOR_SCREEN, SCREEN_COUNT };

class UI {
private:
  TFT_eSPI _tft;
  Screen _currentScreen;
  unsigned long _lastButtonCheck;
  const unsigned long DEBOUNCE_DELAY = 200;

  void drawBuzzerScreen();
  void drawLedScreen();
  void drawSensorScreen(); // <-- Nouvelle méthode pour les capteurs

public:
  UI();
  void begin();
  void drawCurrentScreen();
  void loop();
};

#endif // UI_H

