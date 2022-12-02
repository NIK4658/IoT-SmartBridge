#ifndef __STATE__
#define __STATE__

#include "Task.h"
#include "Led.h"
#include "Sonar.h"
#include "Arduino.h"
#include "ServoTimer2.h"
#include "LCD.h"
#include "Potentiometer.h"
#include "Button.h"

enum class blinkState {
  WAIT,
  BLINK,
  DISABLED,
};

enum class LCDState {
  DISABLED,
  ENABLED,
  ENABLED_WITHVALVE,
};

enum class ManualMode {
  DISABLED,
  ENABLED,
  VIRTUAL,
};

class State: public Task {
 
public:

  State(String name, Led* led1, Led* led2, Sonar* sonar, ServoTimer2* motor, LCD* lcd, Potentiometer* pot, Button* btn, LCDState lcdState, int statusLed1, int statusLed2, double minWaterDistance, double maxWaterDistance, double WL_MIN, bool manualOperations, int minValve, int maxValve);

  void init(int period);

  void tick();

  double minWaterDistance;
  double maxWaterDistance;

protected:

  bool checkWaterLevel();

  void updateLeds();

  void updateValve();

  void updateLCD();

private:
  String name;
  ServoTimer2* motor;
  Led* led1;
  Led* led2;
  LCD* lcd;
  Button* btn;
  Sonar* sonar;
  Potentiometer* pot;
  LCDState lcdState;

  int statusLed1;
  int statusLed2;
  int valveDegrees;
  bool manualOperations;
  uint32_t prevTime;
  double WL_MIN;
  int minValve;
  int maxValve;
  ManualMode manualMode;
  blinkState blink;
};

#endif