#include "State.h"
#include "Led.h"
#include "Arduino.h"


State::State(String name, Led* green, Led* red, Sonar* sonar, ServoMotor* motor, int statusGreen, int statusRed, double minWaterLevel, double maxWaterLevel, int waterSamplingRate, int manualOperations, int minValve, int maxValve){
  this->name = name;
  this->green = green;
  this->red = red;
  this->sonar = sonar;
  this->motor = motor;
  this->statusGreen = statusGreen;
  this->statusRed = statusRed;
  this->minWaterLevel = minWaterLevel;
  this->maxWaterLevel = maxWaterLevel;
  this->waterSamplingRate = waterSamplingRate;
  this->manualOperations = manualOperations; 
  this->minValve=minValve;
  this->maxValve=maxValve;
  this->prevTime=0;
  this->blink = blinkState::BLINK;
}

void State::init(int period){
  Task::init(period);
  valveDegrees = 0;
}

int State::getWaterLevel(){
  return 0;
}


bool State::checkWaterLevel(){
  this->sonar->MeasureDistance();
  return (this->sonar->getLastDistance() > this->minWaterLevel && this->sonar->getLastDistance() <= this->maxWaterLevel);
}

void State::updateLCD(){
  
}

void State::updateValve(){
  int value=map(this->sonar->getLastDistance()*100, this->minWaterLevel*100, this->maxWaterLevel*100, this->maxValve, this->minValve);
  Serial.println(String(this->sonar->getLastDistance()*100));
  Serial.println(value);
  motor->on();
  motor->setPosition(value);
  //delay(30);            
  //motor->off();
}

void State::updateLeds(){
  if(this->statusGreen == 1){
    this->green->switchOn();
  }else{
    this->green->switchOff();
  }

  if(this->statusRed == 1){
    this->red->switchOn();
  }else{
    if(this->statusRed == 0){
      this->red->switchOff();
    }else{
      uint32_t currentTime=millis();
      switch(this->blink) {
        case blinkState::WAIT:
        if((currentTime-this->prevTime)>=this->statusRed){
          prevTime=currentTime;
          this->blink=blinkState::BLINK;
        }
        break;

        case blinkState::BLINK:
        if(this->red->isOn()){
          this->red->switchOff();
        }else{
          this->red->switchOn();
        }
        this->blink=blinkState::WAIT;
        break;
      }
    }
  }
}

void State::tick(){
  if(this->checkWaterLevel()){
    this->updateLeds();
    this->updateLCD();
    if(this->minValve!=this->maxValve){
      //this->updateValve();      
    }
  }else{
    Task::setActive(false);
  }
}
