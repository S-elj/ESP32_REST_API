#include "Led.h"
#include "esp32-hal-adc.h"
#include "esp32-hal.h"
#include <stdint.h>

double MAX_VALUE = 4095.0;

Led::Led(uint8_t ledPin, uint8_t photocellPin) {
  this->_ledPin = ledPin;
  this->_photocellPin = photocellPin;
  this->_threshold = -1;
  this->_automatic = false;
}

bool Led::is_automatic() { return this->_automatic; }

void Led::set_automatic(bool automatic) { this->_automatic = automatic; }

double Led::get_luminosity() {
  if (!this->is_automatic())
    return (this->get_threshold() * MAX_VALUE <=
            analogRead(this->_photocellPin))
               ? this->_luminosity
               : 0.0;
  return (double)analogRead(this->_photocellPin) / MAX_VALUE;
}

void Led::set_luminosity(double value) {
  if (this->is_automatic()) {
    this->set_automatic(false);
  }
  this->_luminosity = value;
}

void Led::set_threshold(double threshold) {
  if (this->is_automatic()) {
    this->set_automatic(false);
  }
  this->_threshold = threshold;
}

double Led::get_threshold() { return this->_threshold; }

void Led::loop() { analogWrite(LED_PIN, (int)(this->get_luminosity() * 255)); }

Led led = Led(LED_PIN, PHOTOCELL_PIN);
