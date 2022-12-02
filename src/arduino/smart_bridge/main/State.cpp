#include "State.h"
#include "Led.h"
#include "Arduino.h"
#include "MsgService.h"


State::State(String name, Led* led1, Led* led2, Sonar* sonar, ServoTimer2* motor, LCD* lcd, Potentiometer* pot, Button* btn, LCDState lcdState, int statusLed1, int statusLed2, double minWaterDistance, double maxWaterDistance, double WL_MIN, bool manualOperations, int minValve, int maxValve){
  this->name = name;
  this->led1 = led1;
  this->led2 = led2;
  this->lcd = lcd;
  this->sonar = sonar;
  this->motor = motor;
  this->btn=btn;
  this->pot=pot;
  this->lcdState = lcdState;
  this->statusLed1 = statusLed1;
  this->statusLed2 = statusLed2;
  this->WL_MIN=WL_MIN;
  this->minWaterDistance = minWaterDistance;
  this->maxWaterDistance = maxWaterDistance;
  this->manualOperations = manualOperations; 
  this->manualMode=ManualMode::DISABLED;
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
  return (this->sonar->getLastDistance() > this->minWaterDistance && this->sonar->getLastDistance() <= this->maxWaterDistance);
}

void State::updateLCD(){
  if(this->lcdState==LCDState::ENABLED || this->lcdState==LCDState::ENABLED_WITHVALVE){
    this->lcd->setON(true);
    this->lcd->clear();
    this->lcd->setWaterLevel(this->WL_MIN-this->sonar->getLastDistance());
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
    this->valveDegrees = map(this->sonar->getLastDistance()*100, this->minWaterDistance*100, this->maxWaterDistance*100, this->maxValve, this->minValve);
  }else{
    this->valveDegrees = this->minValve;
  }

  if(this->manualOperations && btn->checkChangeState()){
    switch(this->manualMode){
      case ManualMode::DISABLED:
      this->manualMode=ManualMode::ENABLED;
      break;
      case ManualMode::ENABLED:
      this->manualMode=ManualMode::DISABLED;
      break;
    }
  }

  if(this->manualOperations && this->manualMode==ManualMode::ENABLED){
    this->valveDegrees = map(pot->getAnalogValue(), 0, 1023, this->maxValve, this->minValve) ;
  }
  
  motor->write(750 + this->valveDegrees*coeff);   
}

void State::updateLeds(){
  this->led1->setState(this->statusLed1 == 1);

  if(this->statusLed2 > 1){
    uint32_t currentTime=millis();
      switch(this->blink) {
        case blinkState::WAIT:
        if((currentTime-this->prevTime)>=this->statusLed2){
          prevTime=currentTime;
          this->blink=blinkState::BLINK;
        }
        break;
        case blinkState::BLINK:
        this->led2->setState(!this->led2->isOn());
        this->blink=blinkState::WAIT;
        break;
      }
  }else{
    this->led2->setState(this->statusLed2 == 1);
  }
}

void State::tick(){
  if(this->checkWaterLevel()){
    this->updateLeds();
    this->updateValve();  
    this->updateLCD();
    MsgService.sendMsg("State:" + String(this->name));
    MsgService.sendMsg("WaterLevel:" + String(this->WL_MIN-this->sonar->getLastDistance()));
  }
}
