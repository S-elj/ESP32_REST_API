#ifndef BUZZER_H
#define BUZZER_H

class Buzzer
{
private:
    int _pin;

public:
    Buzzer(int pin);

    void buzz(unsigned long delay, unsigned long duration);

    void stop();
};

#endif BUZZER_H