#ifndef __LIGHTTASK__
#define __LIGHTTASK__

#include "Task.h"
#include "Led.h"

class LightTask: public Task {

public:

  LightTask();  
  void init(int period);  
  void tick();
};

#endif