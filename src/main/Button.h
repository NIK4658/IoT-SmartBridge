#ifndef __BUTTON__
#define __BUTTON__

class Button {
 
public: 
  Button(int pin);
  bool isPressed();
  bool checkChangeState();

private:
  int pin;
  bool lastValue;
};

#endif