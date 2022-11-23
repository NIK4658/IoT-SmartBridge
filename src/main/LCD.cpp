#include "LCD.h"
#include "Arduino.h"
#include <LiquidCrystal_I2C.h> 

/* Wiring: SDA => A4, SCL => A5 */
/* I2C address of the LCD: 0x27 */
/* Number of columns: 20 rows: 4 */

LCD::LCD(){
  this->state="";
  this->waterLevel=0;
  this->isON = false;  
}

void LCD::init(){
  lcd.init();
}

void LCD::setWaterLevel(int value){
  this->waterLevel=value;
  lcd.setCursor(2, 2); // Set the cursor on the third column and first row.
  lcd.print("Water level:" + String(value));
}

void LCD::setState(String value){
  this->state=value;
  lcd.setCursor(2, 1); // Set the cursor on the third column and first row.
  lcd.print("State: "+String(value));
}

void LCD::setON(bool flag){
  this->isON=flag;
  if(flag){
    lcd.backlight();
  }else{
    lcd.noBacklight();
  }
  //this->lcd->setBacklight(flag);
}

void LCD::clear(){
  lcd.clear();
}

bool LCD::isOn(){
  return this->isON;
}
