#include "Potentiometer.h"
#include "Arduino.h"

Potentiometer::Potentiometer(int pin){
  this->pin = pin;
  pinMode(pin, INPUT);
}

int Potentiometer::getAnalogValue(){
  return analogRead(this->pin);
}

