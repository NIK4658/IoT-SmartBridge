#include "LightTask.h"
#include "Arduino.h"
#include "Led.h"
#include "Pir.h"
#include "LightSensor.h"
#include "MsgService.h"

LightTask::LightTask(Pir* pir, Led* led, LightSensor* ls, int treshold, int T1){ 
  this->pir = pir;
  this->led = led;
  this->ls = ls;
  this->lightTreshold = treshold;
  this->T1 = T1;
  this->lastEvent=0;
  this->lastValue = false;
}
  
void LightTask::init(int period){
  Task::init(period); 
}

void LightTask::turnLedOff(){
  if(led->isOn()){
    led->switchOff();
    this->lastValue=false;
    MsgService.sendMsg("Smart Light:0");
  }
}
  
void LightTask::tick(){
  bool value = (ls->getLuminosity()<this->lightTreshold) && this->pir->checkDifference();
  uint32_t currentTime=millis();
  if(value){
    this->lastEvent=currentTime;
  }
  if(!value && ((currentTime-this->lastEvent)<this->T1) && led->isOn()){
    value=true;
  }

  if(ls->getLuminosity()>this->lightTreshold){
    value=false;
  }

  led->setState(value);
  if(value!=this->lastValue){
    MsgService.sendMsg("Smart Light:" + String(value));
  }
  this->lastValue=value;
}