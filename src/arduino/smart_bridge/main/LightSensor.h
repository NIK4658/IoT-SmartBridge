#ifndef __LIGHTSENSOR__
#define __LIGHTSENSOR__

class LightSensor { 
  
public:
  LightSensor(int pin);
  int getLuminosity();
private:
  int pin;  
};

#endif