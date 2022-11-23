#include "StateActivator.h"
#include "Sonar.h"


StateActivator::StateActivator(State* normalState, State* preAlarmState, State* alarmState, Sonar* sonar){
  this->sonar = sonar;
  this->states[0]=normalState;
  this->states[1]=preAlarmState;
  this->states[2]=alarmState;
}

void StateActivator::init(int period){
  Task::init(period);
}


void StateActivator::tick(){
  for (int i=0; i<sizeof states /sizeof states[0]; i++) {
    this->states[i]->setActive(this->sonar->MeasureDistance() > this->states[i]->minWaterLevel && this->sonar->MeasureDistance() <= this->states[i]->maxWaterLevel);
  }
}