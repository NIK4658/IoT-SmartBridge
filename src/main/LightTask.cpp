#include "LightTask.h"
#include "Arduino.h"
#include "Led.h"
#include "Pir.h"
#include "LightSensor.h"

LightTask::LightTask(Pir* pir, Led* led, LightSensor* ls, int treshold){ 
  this->pir = pir;
  this->led = led;
  this->ls = ls;
  this->lightTreshold = treshold;
}
  
void LightTask::init(int period){
  Task::init(period); 
}

void LightTask::turnLedOff(){
  led->switchOff();
}
  
void LightTask::tick(){
  led->setState((ls->getLuminosity()<this->lightTreshold) && this->pir->checkDifference());
}