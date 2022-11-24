#include "Button.h"
#include "Arduino.h"

Button::Button(int pin){
  this->pin = pin;
  this->lastValue=false;
  pinMode(pin, INPUT);     
} 
  
bool Button::isPressed(){
  return digitalRead(pin) == HIGH;
}

bool Button::checkChangeState(){
  bool state = isPressed();
  bool value = ((state && this->lastValue==0));
  this->lastValue = state;
  Serial.println(value);
  return value;
}