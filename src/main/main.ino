//Montanari Nicola

#include "Scheduler.h"
#include "Task.h"
#include "Led.h"
#include "State.h"
#include "Sonar.h"
#include "StateActivator.h"
#include "Pir.h"
#include "LightSensor.h"
#include "ServoMotor.h"
#include "LCD.h"
#include "LightTask.h"

#include <LiquidCrystal_I2C.h> 

//Definizioni PINS

#define ledA 7 	//Green for lightning
#define ledB 5 	//Green for bridge status
#define ledC 6 	//Red for alarm state

#define LS A1 	//Light Sensor
#define PIR 1 	//PIR
#define POT A0 	//Valve controller
#define BTN 8 	//Manual mode
#define Sonarr 4 //Sonar ping
#define Motor 9 //Servo Motor (Valve)

//Definizioni Costanti

#define TH_L 100 //Light Treshold (DA DEFINIRE)

#define WL_1 100	//Water level normal (DA DEFINIRE)
#define WL_2 200	//Water level pre alarm (DA DEFINIRE)
#define WL_MAX 300	//Water level alarm (DA DEFINIRE)

#define PE_Normal 500 	//Sampling Rate Water level Normal (DA DEFINIRE)
#define PE_PreAlarm 350	//Sampling Rate Water level PreAlarm (DA DEFINIRE)
#define PE_Alarm 200	//Sampling Rate Water level Alarm (DA DEFINIRE)


//Definizione Variabili

Scheduler sched;
Sonar* sonar;
Task* normalState;
Task* preAlarmState;
Task* alarmState;
Pir* pir;
LightSensor* ls;
Led* green;
Led* red;
Led* people;
ServoMotor* motor;
int pos;
int delta;

LCD* lcd;

Task* newTask;

int manualenabled=0;

//LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4);

void setup()
{
  Serial.begin(9600);
  sched.init(250);

  //Task* lights = new LightTask(pin);
  //lights->init(500);

  green = new Led(3);
  red = new Led(4);
  people = new Led(2);

  sonar = new Sonar(13,12);

  newTask = new LightTask(); 
  newTask->init(500);

  normalState = new State(green, red, sonar, 1, 2000, 0, 40, 10, 1);
  normalState->init(PE_Normal);

  preAlarmState = new State(green, red, sonar, 0, 1, 100, 150, 10, 1);
  preAlarmState->init(PE_PreAlarm);

  alarmState = new State(green, red, sonar, 1, 1, 151, 300, 10, 1);
  alarmState->init(PE_Alarm);



  Task* StateActivatorr = new StateActivator(normalState, preAlarmState, alarmState, sonar);
  StateActivatorr->init(100);

  //sched.addTask(lights);
  sched.addTask(StateActivatorr);
  sched.addTask(normalState);
  //sched.addTask(newTask);
  //sched.addTask(preAlarmState);
  //sched.addTask(alarmState);

  //ls = new LightSensor(A0);
  //pir = new Pir(8);

  motor = new ServoMotor(A1);

  pos = 0;
  delta = 1;
  
  lcd = new LCD();
  //lcd->init();

  lcd->init();
  //lcd.backlight();
}

void loop()
{
  
  //sched.schedule();
  Serial.println(digitalRead(7));

  /*
  if(digitalRead(7)==HIGH){
    manualenabled=1;
  }else{
    manualenabled=0;
  }
  */

  //Serial.println(digitalRead(5));
  //lcd->setState("Normal");

  //people->switchOn();

  /*
  delay(1000);
  lcd.setCursor(1, 1);
  lcd.print("Status: Normal");
  delay(1000);
  lcd.setCursor(1, 2);
  pos++;
  lcd.print("Water: "+String(pos));
  delay(1000);
  lcd.noBacklight();
 
  */

/*
  delay(1000);
  lcd->setState("Normal");
  delay(1000);
  pos++;
  lcd->setWaterLevel(pos);
  delay(1000);
  lcd->clear();
  //Serial.println(lcd->isOn());
  lcd->setON(false);
  */

  while(digitalRead(7)==HIGH){
    motor->on();
    Serial.println(pos);
    motor->setPosition(pos);         
    //delay(2);            
    pos = map(analogRead(A2), 0, 1023, 0, 179);
    lcd->setState(String(pos));
  }
  motor->off();


  //delay(1000);

  
  
  
  /*
  motor->on();
  
  Serial.println(String(pos));
  motor->setPosition(10);    
  motor->off();
  delay(1000);
  */



  /*
  if(ls->getLuminosity()<300 && pir->checkDifference()==1){
    green->switchOn();
    red->switchOn();
  }else{
    green->switchOff();
    red->switchOff();
  }
  Serial.println(ls->getLuminosity());
  */

  /*
  Serial.println(sonar->getLastDistance());
  Serial.print("NormalState:");
  Serial.println(normalState->isActive());
  Serial.print("preAlarmState:");
  Serial.println(preAlarmState->isActive());
  Serial.print("AlarmState:");
  Serial.println(alarmState->isActive());
  */
}