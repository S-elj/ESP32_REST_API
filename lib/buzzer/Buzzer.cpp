#include "Buzzer.h"
#include "Arduino.h"

// Initialise le buzzer au pin indiqué.
Buzzer::Buzzer(uint8_t pin) {
  _pin = pin;
  timestampDepart = 0;
  timestampFin = 0;
}

// Prépare un futur buzzer
void Buzzer::buzz(unsigned long _delay, unsigned long duration) {
  timestampDepart = esp_log_timestamp() + _delay;
  timestampFin = timestampDepart + duration;
}

// Retourne `true` si un buzzer est planifié
boolean Buzzer::is_planned() {
  return timestampDepart != 0 && timestampFin != 0;
}

// Retourne `true` si le buzzer est planifié & qu'il a démarré.
boolean Buzzer::has_started() { return timestampDepart <= esp_log_timestamp(); }

// Return `true` si le buzzer était planifié et qu'il est terminé.
boolean Buzzer::has_finished() { return timestampFin <= esp_log_timestamp(); }

// Retourne le temps restant au buzzer avant de s'arrêter, ce temps n'a pas de
// sens si le timer n'a pas commencé, penser à utiliser `has_started` et
// `has_finished`
long Buzzer::time_remaining() { return timestampFin - esp_log_timestamp(); }

long Buzzer::time_until_start() {
  return timestampDepart - esp_log_timestamp();
}

// Arrête le buzzer
void Buzzer::stop() {
  timestampDepart = 0;
  timestampFin = 0;
  noTone(_pin);
}

// S'exécute au niveau de la loupe afin de s'assurer d'avoir un buzzer qui
// tourne en continue.
//
// Effectuer l'action au niveau de la loupe nous permet d'avoir un Buzzer qui
// tourne en continue sans pour autant nécessiter un bloquage I/O.
void Buzzer::loop() {
  if (!is_planned() || !has_started())
    return;

  if (!has_finished()) {
    tone(_pin, 1109, 101);
  } else {
    stop();
  }
}

Buzzer buzzer = Buzzer(BUZZER_PIN);
