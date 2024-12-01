#include "Buzzer.h"
#include "Arduino.h"

Buzzer::Buzzer(int pin) : _pin(pin)
{
    pinMode(_pin, OUTPUT);
}

void Buzzer::buzz(unsigned long delay, unsigned long duration)
{
    delay(delay);
    digitalWrite(_pin, HIGH);
    delay(duration);
    digitalWrite(_pin, LOW);
}

void Buzzer::stop()
{
    digitalWrite(_pin, low);
}