#include "Led.h"
#include "esp32-hal-adc.h"
#include "esp32-hal.h"
#include <stdint.h>

Led::Led(uint8_t ledPin, uint8_t photocellPin) {
  this->_ledPin = ledPin;
  this->_photocellPin = photocellPin;
  this->_automatic = false;
}

bool Led::is_automatic() {
  return this->_automatic;
}

void Led::set_automatic(bool automatic) {
  this->_automatic = automatic;
}

double Led::get_luminosity() {
  if (!this->is_automatic())
    return this->_luminosity;
  uint16_t hue = analogRead(this->_photocellPin);
  return (double)hue / 4095.0;
}

void Led::set_luminosity(double value) {
  if (this->is_automatic()) {
    this->set_automatic(false);
  }
  this->_luminosity = value;
}

void Led::loop() {
  analogWrite(LED_PIN, (int) (this->get_luminosity()  * 255));
}

Led led = Led(LED_PIN, PHOTOCELL_PIN);
