#include "LightSensor.h"
#include "Arduino.h"

LightSensor::LightSensor(int pin){
  this->pin = pin;
  pinMode(pin, INPUT);
}

int LightSensor::getLuminosity(){
  return analogRead(this->pin);
}

