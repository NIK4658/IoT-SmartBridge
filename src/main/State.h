#ifndef __STATE__
#define __STATE__

#include "Task.h"
#include "Led.h"
#include "Sonar.h"

class State: public Task {
 
public:

  State(Led* green, Led* red, Sonar* sonar, int statusGreen, int statusRed, double minWaterLevel, double maxWaterLevel, int waterSamplingRate, int manualOperations);

  void init(int period);

  void tick();

  double minWaterLevel;
  double maxWaterLevel;

protected:

  int getWaterLevel();

  bool checkWaterLevel();

  void updateLeds();

  void updateLCD();

private:
  Led* green;
  Led* red;
  Sonar* sonar;
  int statusGreen;
  int statusRed;
  int waterSamplingRate;
  int valveDegrees;
  int manualOperations;
};

#endif