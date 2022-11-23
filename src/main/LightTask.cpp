#include "LightTask.h"
#include "Arduino.h"

LightTask::LightTask(){ 
}
  
void LightTask::init(int period){
  Task::init(period); 
}
  
void LightTask::tick(){
  Serial.print(String(1));
}