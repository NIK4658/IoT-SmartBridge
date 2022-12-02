#include "LCD.h"
#include "Arduino.h"
#include <LiquidCrystal_I2C.h> 

LCD::LCD(){
  this->state="";
  this->waterLevel=0;
  this->isON = false;  
}

void LCD::init(){
  lcd.init();
  lcd.backlight();
}

void LCD::setWaterLevel(float value){
  this->waterLevel=value;
  lcd.setCursor(2, 1); 
  lcd.print("Water level:" + String(this->waterLevel));
}

void LCD::setState(String value){
  this->state=value;
  lcd.setCursor(2, 0); 
  lcd.print("State: "+String(this->state));
}

void LCD::setValve(int value){
  lcd.setCursor(2, 2);
  lcd.print("Valve: "+String(value));
}

void LCD::setON(bool flag){
  this->isON=flag;
  if(flag){
    lcd.backlight();
  }else{
    lcd.noBacklight();
    this->clear();
  }
}

void LCD::clear(){
  lcd.clear();
}

bool LCD::isOn(){
  return this->isON;
}
