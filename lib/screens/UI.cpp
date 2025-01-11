#include "UI.h"
#include "Buzzer.h"
#include "Led.h"

#define BUTTON_1 0  // Bouton pour avancer
#define BUTTON_2 35 // Bouton pour reculer

UI::UI() {
  _currentScreen = BUZZER_SCREEN;
  _lastButtonCheck = 0;
}

void UI::begin() {
  _tft.init();
  _tft.setRotation(1); // Mode paysage

  // Configuration des boutons
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);

  // Affichage initial
  drawCurrentScreen();
}

void UI::drawBuzzerScreen() {
  _tft.fillScreen(TFT_BLACK);
  _tft.setTextSize(2);
  _tft.setTextColor(TFT_WHITE);

  _tft.drawString("Minuteur", 10, 10);
  _tft.setTextSize(1);

  if (buzzer.is_planned()) {
    if (buzzer.has_started()) {
      _tft.setTextColor(TFT_GREEN);
      _tft.drawString("ACTIF", 10, 40);
      char timeStr[22];
      sprintf(timeStr, "Temps restant: %0.2f s",
              buzzer.timeRemaining() / 1000.0);
      _tft.drawString(timeStr, 10, 60);
    } else {
      _tft.setTextColor(TFT_YELLOW);
      _tft.drawString("PLANIFIÉ", 10, 40);
      char timeStr[22];
      sprintf(timeStr, "Commence dans: %0.2f s",
              buzzer.timeUntilStart() / 1000.0);
      _tft.drawString(timeStr, 10, 60);
    }
  } else {
    _tft.setTextColor(TFT_RED);
    _tft.drawString("Inactif...", 10, 40);
  }

  _tft.setTextColor(TFT_BLUE);
  _tft.drawString("LEFT: Prev | RIGHT: Next", 10, _tft.height() - 20);
}

void UI::drawLedScreen() {
  _tft.fillScreen(TFT_BLACK);
  _tft.setTextSize(2);
  _tft.setTextColor(TFT_WHITE);

  _tft.drawString("LED", 10, 10);
  _tft.setTextSize(1);

  _tft.setTextColor(TFT_GREEN);
  _tft.drawString(led.is_automatic() ? "Mode: AUTOMATIQUE" : "Mode: MANUEL", 10,
                  40);

  char lumStr[20];
  sprintf(lumStr, "Luminosite: %.1f%%", led.get_luminosity() * 100);
  _tft.drawString(lumStr, 10, 60);

  if (!led.is_automatic() && led.get_threshold() > 0) {
    char threshStr[20];
    sprintf(threshStr, "Seuille: %.1f%%", led.get_threshold() * 100);
    _tft.drawString(threshStr, 10, 80);
  }

  _tft.setTextColor(TFT_BLUE);
  _tft.drawString("LEFT: Prev | RIGHT: Next", 10, _tft.height() - 20);
}

void UI::drawSensorScreen() {
  _tft.fillScreen(TFT_BLACK);
  _tft.setTextSize(2);
  _tft.setTextColor(TFT_WHITE);

  _tft.drawString("Capteurs", 10, 10);
  _tft.setTextSize(1);

  int photocellValue = analogRead(PHOTOCELL_PIN);
  int thermistorValue = analogRead(THERMISTOR_PIN);

  char photoStr[30];
  sprintf(photoStr, "Photocell: %d", photocellValue);
  _tft.setTextColor(TFT_YELLOW);
  _tft.drawString(photoStr, 10, 40);

  char thermoStr[30];
  sprintf(thermoStr, "Thermistor: %d", thermistorValue);
  _tft.setTextColor(TFT_CYAN);
  _tft.drawString(thermoStr, 10, 60);

  _tft.setTextColor(TFT_BLUE);
  _tft.drawString("LEFT: Prev | RIGHT: Next", 10, _tft.height() - 20);
}

void UI::drawCurrentScreen() {
  switch (_currentScreen) {
  case BUZZER_SCREEN:
    drawBuzzerScreen();
    break;
  case LED_SCREEN:
    drawLedScreen();
    break;
  case SENSOR_SCREEN:
    drawSensorScreen();
    break;
  }
}

void UI::loop() {
  if (millis() - _lastButtonCheck >= DEBOUNCE_DELAY) {
    if (digitalRead(BUTTON_1) == LOW) {
      _currentScreen = static_cast<Screen>((_currentScreen + 1) % SCREEN_COUNT);
      drawCurrentScreen();
      _lastButtonCheck = millis();
    } else if (digitalRead(BUTTON_2) == LOW) {
      _currentScreen = static_cast<Screen>(
          _currentScreen == 0 ? SCREEN_COUNT - 1 : _currentScreen - 1);
      drawCurrentScreen();
      _lastButtonCheck = millis();
    }
  }

  static unsigned long lastRefresh = 0;
  if (millis() - lastRefresh >= 1000) {
    drawCurrentScreen();
    lastRefresh = millis();
  }
}

