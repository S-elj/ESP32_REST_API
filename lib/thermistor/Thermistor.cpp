#include "Thermistor.h"
#include "HardwareSerial.h"

#define ADC_MAX 4095
#define VREF 3.3
#define PULLUP_RESISTOR 10000
#define R0 10000
#define T0 298.15
#define A 1.313573481e-3
#define B 2.027414875e-4
#define C 2.215809202e-7

#define CALIBRATION_FACTOR 1.4;

// Je ne sais pas si c'est moi mais j'ai l'impression que le capteur est une
// cata, les valeurs semblent complètement à côté de la plaque et j'ai tout
// essayé...
float to_degrees(int adcValue) {
  // Calcul de la tension mesurée par l'ADC
  float voltage = (VREF * adcValue) / ADC_MAX;

  // Calcul de la résistance du thermistor
  float resistance = (PULLUP_RESISTOR * voltage) / (VREF - voltage);
  resistance *= CALIBRATION_FACTOR;

  // Calcul de la température avec l'équation de Steinhart-Hart
  float logR = log(resistance);
  float temperatureK = 1.0 / (A + (B * logR) + (C * logR * logR * logR));
  float temperatureC = temperatureK - 273.15;

  return temperatureC;
}

/**const float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
float to_degrees(int thermistorReading) {
  float thermistorResistor =
      PULLUP_RESISTOR * (ADC_MAX / (float)thermistorReading - 1.0);
  float logR2 = log(thermistorResistor);
  float T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  float Tc = T - 273.15;
  return Tc;
}**/
