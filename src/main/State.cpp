#include "State.h"
#include "Led.h"
#include "Arduino.h"


State::State(String name, Led* green, Led* red, Sonar* sonar, ServoTimer2* motor, LCD* lcd, Potentiometer* pot, Button* btn, LCDState lcdState, int statusGreen, int statusRed, double minWaterLevel, double maxWaterLevel, bool manualOperations, int minValve, int maxValve){
  this->name = name;
  this->green = green;
  this->red = red;
  this->lcd = lcd;
  this->sonar = sonar;
  this->motor = motor;
  this->lcdState = lcdState;
  this->statusGreen = statusGreen;
  this->statusRed = statusRed;
  this->btn=btn;
  this->pot=pot;
  this->minWaterLevel = minWaterLevel;
  this->maxWaterLevel = maxWaterLevel;
  this->manualOperations = manualOperations; 
  this->manualMode=false;
  this->minValve=minValve;
  this->maxValve=maxValve;
  this->prevTime=0;
  this->valveDegrees = 0;
  this->blink = blinkState::BLINK;
}

void State::init(int period){
  Task::init(period);
}

bool State::checkWaterLevel(){
  this->sonar->MeasureDistance();
  return (this->sonar->getLastDistance() > this->minWaterLevel && this->sonar->getLastDistance() <= this->maxWaterLevel);
}

void State::updateLCD(){
  if(this->lcdState==LCDState::ENABLED || this->lcdState==LCDState::ENABLED_WITHVALVE){
    this->lcd->setON(true);
    this->lcd->clear();
    this->lcd->setWaterLevel(this->sonar->getLastDistance());
    this->lcd->setState(this->name);
    if(this->lcdState==LCDState::ENABLED_WITHVALVE){
      this->lcd->setValve(this->valveDegrees);
    }
  }else{
    this->lcd->setON(false);
  }
}

void State::updateValve(){
  float coeff = (2250.0-750.0)/180;
  if(this->minValve!=this->maxValve){
    this->valveDegrees = map(this->sonar->getLastDistance()*100, this->minWaterLevel*100, this->maxWaterLevel*100, this->maxValve, this->minValve);
  }else{
    this->valveDegrees = this->minValve;
  }

  if(this->manualOperations && btn->checkChangeState()){
    this->manualMode = !(this->manualMode);
  }

  if(this->manualOperations && this->manualMode){
    this->valveDegrees = map(pot->getAnalogValue(), 0, 1023, this->maxValve, this->minValve) ;
  }

  motor->write(750 + this->valveDegrees*coeff);   
}

void State::updateLeds(){
  this->green->setState(this->statusGreen == 1);

  if(this->statusRed > 1){
    uint32_t currentTime=millis();
      switch(this->blink) {
        case blinkState::WAIT:
        if((currentTime-this->prevTime)>=this->statusRed){
          prevTime=currentTime;
          this->blink=blinkState::BLINK;
        }
        break;
        case blinkState::BLINK:
        this->red->setState(!this->red->isOn());
        this->blink=blinkState::WAIT;
        break;
      }
  }else{
    this->red->setState(this->statusRed == 1);
  }
}

void State::tick(){
  if(this->checkWaterLevel()){
    this->updateLeds();
    this->updateValve();  
    this->updateLCD();
  }
}
