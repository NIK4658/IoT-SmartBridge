#include "ServoMotor.h"
#include "Arduino.h"

ServoMotor::ServoMotor(int pin){
  this->pin = pin;  
} 

void ServoMotor::on(){
  motor.attach(pin);    
}

void ServoMotor::setPosition(int angle){
  //this->on();
  //for(int i=0; i<10; i++){
  motor.write(angle);
  //}
  //this->off();   
}

void ServoMotor::off(){
  motor.detach();    
}