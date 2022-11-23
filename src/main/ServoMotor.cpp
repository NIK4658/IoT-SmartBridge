#include "ServoMotor.h"
#include "Arduino.h"

ServoMotor::ServoMotor(int pin){
  this->pin = pin;  
  angle=0;
} 

void ServoMotor::on(){
  motor.attach(pin);    
}

int ServoMotor::getAngle(){
  return this->angle;    
}

void ServoMotor::setPosition(int angle){
  //this->on();
  //for(int i=0; i<10; i++){
  motor.write(angle);
  this->angle=angle;
  //}
  //this->off();   
}

void ServoMotor::off(){
  motor.detach();    
}