#include "Buzzer.h"
#include "Arduino.h"


Buzzer::Buzzer(int pin)
{
  _pin = pin;
  timestampDepart = 0;
  timestampFin = 0;
}

void Buzzer::buzz(unsigned long _delay, unsigned long duration)
{
  timestampDepart = esp_log_timestamp() + _delay;
  timestampFin = timestampDepart + duration;
}

boolean Buzzer::is_planned() {
  return timestampDepart != 0 && timestampFin != 0;
}

boolean Buzzer::has_started() {
  return timestampDepart <= esp_log_timestamp();
}

boolean Buzzer::has_finished() {
  return timestampFin <= esp_log_timestamp();
}

void Buzzer::stop()
{
  timestampDepart = 0;
  timestampFin = 0;
  noTone(_pin);
}

void Buzzer::loop() {
  if (!is_planned() || !has_started()) return;

  if (!has_finished()) {
    tone(_pin, 1109, 201);
  } else {
    stop();
  }
}

Buzzer buzzer = Buzzer(2);
