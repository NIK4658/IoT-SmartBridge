#ifndef __STATEACTIVATOR__
#define __STATEACTIVATOR__

#include "Task.h"
#include "State.h"
#include "Sonar.h"
#include "LightTask.h"

class StateActivator: public Task {
 
public:

  StateActivator(State* normalState, State* preAlarmState, State* alarmState, LightTask* lights, Sonar* sonar, bool lightsEnabled1, bool lightsEnabled2, bool lightsEnabled3);
  void init(int period);
  void tick();

private:
  Sonar* sonar;
  State* states[3];
  bool lightsEnabled[3];
  LightTask* lightsTask;
};

#endif