#include "StateActivator.h"
#include "Sonar.h"


StateActivator::StateActivator(State* normalState, State* preAlarmState, State* alarmState, LightTask* lights, Sonar* sonar, bool lightsEnabled1, bool lightsEnabled2, bool lightsEnabled3){
  this->sonar = sonar;
  this->states[0]=normalState;
  this->states[1]=preAlarmState;
  this->states[2]=alarmState;
  this->lights=lights;
  this->lightsEnabled[0]=lightsEnabled1;
  this->lightsEnabled[1]=lightsEnabled2;
  this->lightsEnabled[2]=lightsEnabled3;
}

void StateActivator::init(int period){
  Task::init(period);
}


void StateActivator::tick(){
  this->lights->setActive(false);
  for (int i=0; i<sizeof states / sizeof states[0]; i++) {
    this->states[i]->setActive(this->sonar->MeasureDistance() > this->states[i]->minWaterLevel && this->sonar->MeasureDistance() <= this->states[i]->maxWaterLevel);
    if(this->states[i]->isActive() && this->lightsEnabled[i]==true){
      this->lights->setActive(true);
    }
  }
  if(this->lights->isActive()==false){
    this->lights->turnLedOff();
  }
}