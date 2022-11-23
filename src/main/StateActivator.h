#ifndef __STATEACTIVATOR__
#define __STATEACTIVATOR__

#include "Task.h"
#include "State.h"
#include "Sonar.h"

class StateActivator: public Task {
 
public:

  StateActivator(State* normalState, State* preAlarmState, State* alarmState, Sonar* sonar);

  void init(int period);

  void tick();

private:
  Sonar* sonar;
  State* states[3];
};

#endif