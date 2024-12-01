#include <WString.h>

class Sensor {
    public:
        virtual String getType() = 0; 
        virtual float readValue() = 0;
};

class Photocell : public Sensor {
    public:
        String getType() override { return "light"; }
        float readValue() override { 
            
        }
};

class Thermistor : public Sensor {
    public:
        String getType() override { return "temperature"; }
        float readValue() override { 
            
        }
};