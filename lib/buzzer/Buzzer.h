class Buzzer
{
private:
  int _pin;
  long timestampDepart;
  long timestampFin;

public:
  Buzzer(int pin);
  void buzz(unsigned long delay, unsigned long duration);
  bool is_planned();
  bool has_started();
  bool has_finished();
  void stop();
  void loop();
};

extern Buzzer buzzer;
