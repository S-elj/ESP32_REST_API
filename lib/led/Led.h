#include <cstdint>
#include <stdint.h>

class Led {
private:
  bool _automatic;
  double _luminosity;
  double _threshold;
  uint8_t _ledPin;
  uint8_t _photocellPin;

public:
  Led(uint8_t ledPin, uint8_t photocellPin);
  // Retourne `true` si la LED est contrôlé automatiquement
  bool is_automatic();

  // Défini le comportement de la LED afin qu'elle soit contrôlé
  // automatiquement.
  void set_automatic(bool automatic);

  // Défini la luminosité de la LED (valeur entre 0 et 1).
  //
  // Si la LED est contrôlée automatiquement, ce comportement se désactive
  // alors.
  void set_luminosity(double value);

  // Retourne la luminosité de la LED.
  double get_luminosity();

  // Défini un threshold à l'aide d'une valeur entre 0 et 1 pour simplifier le
  // processus.
  void set_threshold(double threshold);

  double get_threshold();

  // S'exécute au niveau de la loupe afin de s'assurer d'avoir le comportement
  // attendu pour la Led.
  void loop();
};

extern Led led;
