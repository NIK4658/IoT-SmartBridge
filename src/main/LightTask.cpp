#include "LightTask.h"
#include "Arduino.h"
#include "Led.h"
#include "Pir.h"
#include "LightSensor.h"
#include "MsgService.h"

LightTask::LightTask(Pir* pir, Led* led, LightSensor* ls, int treshold){ 
  this->pir = pir;
  this->led = led;
  this->ls = ls;
  this->lightTreshold = treshold;
  this->lastValue = false;
}
  
void LightTask::init(int period){
  Task::init(period); 
}

void LightTask::turnLedOff(){
  led->switchOff();
}
  
void LightTask::tick(){
  bool value = (ls->getLuminosity()<this->lightTreshold) && this->pir->checkDifference();
  led->setState(value);
  if(value!=this->lastValue){
    MsgService.sendMsg("Smart Light:" + String(value));
  }
  this->lastValue=value;
}