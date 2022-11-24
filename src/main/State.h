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

  State(String name, Led* green, Led* red, Sonar* sonar, ServoTimer2* motor, LCD* lcd, Potentiometer* pot, Button* btn, LCDState lcdState, int statusGreen, int statusRed, double minWaterLevel, double maxWaterLevel, bool manualOperations, int minValve, int maxValve);

  void init(int period);

  void tick();

  double minWaterLevel;
  double maxWaterLevel;

protected:

  bool checkWaterLevel();

  void updateLeds();

  void updateValve();

  void updateLCD();

private:
  String name;
  ServoTimer2* motor;
  Led* green;
  Led* red;
  LCD* lcd;
  Sonar* sonar;
  Potentiometer* pot;
  LCDState lcdState;
  int statusGreen;
  int statusRed;
  int valveDegrees;
  bool manualOperations;
  uint32_t prevTime;
  Button* btn;
  ManualMode manualMode;
  blinkState blink;
  int minValve;
  int maxValve;
};

#endif