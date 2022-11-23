#ifndef __LIGHTTASK__
#define __LIGHTTASK__

#include "Task.h"
#include "Led.h"
#include "Pir.h"
#include "LightSensor.h"

class LightTask: public Task {

public:

  LightTask(Pir* pir, Led* led, LightSensor* ls, int treshold);  
  void init(int period);  
  void turnLedOff();
  void tick();
private:
  int lightTreshold;
  Led* led;
  LightSensor* ls;
  Pir* pir;
};

#endif