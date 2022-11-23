#ifndef __STATE__
#define __STATE__

#include "Task.h"
#include "Led.h"
#include "Sonar.h"
#include "Arduino.h"
#include "ServoMotor.h"

enum class blinkState {
  WAIT,
  BLINK,
  DISABLED,
};


class State: public Task {
 
public:

  State(String name, Led* green, Led* red, Sonar* sonar, ServoMotor* motor, int statusGreen, int statusRed, double minWaterLevel, double maxWaterLevel, int waterSamplingRate, int manualOperations, int minValve, int maxValve);

  void init(int period);

  void tick();

  double minWaterLevel;
  double maxWaterLevel;

protected:

  int getWaterLevel();

  bool checkWaterLevel();

  void updateLeds();

  void updateValve();

  void updateLCD();

private:
  String name;
  ServoMotor* motor;
  Led* green;
  Led* red;
  Sonar* sonar;
  int statusGreen;
  int statusRed;
  int waterSamplingRate;
  int valveDegrees;
  int manualOperations;
  uint32_t prevTime;
  blinkState blink;
  int minValve;
  int maxValve;
};

#endif