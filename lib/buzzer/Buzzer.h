#include <stdint.h>

class Buzzer {
private:
  uint8_t _pin;
  long timestampDepart;
  long timestampFin;

public:
  // Initialise le buzzer au pin indiqué.
  Buzzer(uint8_t pin);
  // Prépare un futur buzzer
  void buzz(unsigned long delay, unsigned long duration);
  // Retourne `true` si un buzzer est planifié
  bool is_planned();
  // Retourne `true` si le buzzer est planifié & qu'il a démarré.
  bool has_started();
  // Return `true` si le buzzer était planifié et qu'il est terminé.
  bool has_finished();
  // Retourne le temps restant au buzzer avant de s'arrêter, ce temps n'a pas de
  // sens si le timer n'a pas commencé, penser à utiliser `has_started` et
  // `has_finished`
  long timeRemaining();
  // Retourne le temps avant que le buzzer ne démarre. Même remarque que pour
  // `timeRemaining`, penser à utiliser les autres fonctions pour vérifier
  // l'état avant!
  long timeUntilStart();
  // Arrête le buzzer
  void stop();
  // S'exécute au niveau de la loupe afin de s'assurer d'avoir un buzzer qui
  // tourne en continue.
  //
  // Effectuer l'action au niveau de la loupe nous permet d'avoir un Buzzer qui
  // tourne en continue sans pour autant nécessiter un bloquage I/O.
  void loop();
};

extern Buzzer buzzer;
