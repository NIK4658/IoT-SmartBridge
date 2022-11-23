#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

#include <Servo.h>

class ServoMotor {

public:
  ServoMotor(int pin);

  void on();
  void setPosition(int angle);
  int getAngle();
  void off();
    
private:
  int pin; 
  int angle;
  Servo motor; 
};

#endif