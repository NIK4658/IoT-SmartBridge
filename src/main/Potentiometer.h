#ifndef __POTENTIOMETER__
#define __POTENTIOMETER__

class Potentiometer { 
  
public:
  Potentiometer(int pin);
  int getAnalogValue();
private:
  int pin;  
};

#endif