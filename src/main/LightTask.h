#ifndef __LIGHTTASK__
#define __LIGHTTASK__

#include "Task.h"
#include "Led.h"
#include "Pir.h"
#include "LightSensor.h"
#include "Arduino.h"

class LightTask: public Task {

public:

  LightTask(Pir* pir, Led* led, LightSensor* ls, int treshold, int T1);  
  void init(int period);  
  void turnLedOff();
  void tick();
private:
  int lightTreshold;
  bool lastValue;
  int T1;
  uint32_t lastEvent;
  Led* led;
  LightSensor* ls;
  Pir* pir;
};

#endif