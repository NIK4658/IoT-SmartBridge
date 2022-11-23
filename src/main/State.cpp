#include "State.h"
#include "Led.h"


State::State(Led* green, Led* red, Sonar* sonar, int statusGreen, int statusRed, double minWaterLevel, double maxWaterLevel, int waterSamplingRate, int manualOperations){
  this->green = green;
  this->red = red;
  this->sonar = sonar;
  this->statusGreen = statusGreen;
  this->statusRed = statusRed;
  this->minWaterLevel = minWaterLevel;
  this->maxWaterLevel = maxWaterLevel;
  this->waterSamplingRate = waterSamplingRate;
  this->manualOperations = manualOperations; 
}

void State::init(int period){
  Task::init(period);
  valveDegrees = 0;
}

int State::getWaterLevel(){
  return 0;
}


bool State::checkWaterLevel(){
  return (this->sonar->MeasureDistance() > this->minWaterLevel && this->sonar->MeasureDistance() <= this->maxWaterLevel);
}

void State::updateLCD(){
  return true;
}

void State::updateLeds(){
  if(this->statusGreen == 1){
    this->green->switchOn();
  }else{
    if(this->statusGreen == 0){
      this->green->switchOff();
    }else{
      //BLINKING
    }
  }

  if(this->statusRed == 1){
    this->red->switchOn();
  }else{
    if(this->statusRed == 0){
      this->red->switchOff();
    }else{
      //BLINKING
    }
  }
}

void State::tick(){
  if(this->checkWaterLevel()){
    this->updateLeds();
    this->updateLCD();
  }else{
    Task::setActive(false);
  }
}
