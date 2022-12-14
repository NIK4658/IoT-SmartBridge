#ifndef __LCD__
#define __LCD__
#include <LiquidCrystal_I2C.h> 

class LCD { 
  
public:
  LCD();
  void init();

  void setWaterLevel(float value);
  void setValve(int value);
  void setState(String value);
  void setON(bool flag);
  bool isOn();
  void clear();

private:
  float waterLevel;
  String state;  
  bool isON;
  LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4);
};

#endif