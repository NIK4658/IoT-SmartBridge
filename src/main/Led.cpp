#include "Led.h"
#include "Arduino.h"

Led::Led(int pin){
  this->pin = pin;
  this->ON = false;
  pinMode(pin,OUTPUT);
}

void Led::switchOn(){
  digitalWrite(pin,HIGH);
  this->ON = true;
}

void Led::switchOff(){
  digitalWrite(pin,LOW);
  this->ON = false;
};

bool Led::isOn(){
  return this->ON;
};