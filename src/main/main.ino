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

//Definizioni PINS

#define ledA 2 	//Green for lightning
#define ledB 3 	//Green for bridge status
#define ledC 4 	//Red for alarm state

#define LS A0 	//Light Sensor
#define PIR 5 	//PIR
#define POT A2 	//Valve controller
#define BTN 7 	//Manual mode
#define SonarTrig 13 //Sonar trig
#define SonarEcho 12 //Sonar echo
#define Motor A1 //Servo Motor (Valve)

//Definizioni Costanti

#define TH_L 700 //Light Treshold (DA DEFINIRE)

#define WL_1 0.5	//Water level normal (DA DEFINIRE)
#define WL_2 0.4	//Water level pre alarm (DA DEFINIRE)
#define WL_MAX 0.01	//Water level alarm (DA DEFINIRE)

#define PE_Normal 1000 	//Sampling Rate Water level Normal (DA DEFINIRE)
#define PE_PreAlarm 500	//Sampling Rate Water level PreAlarm (DA DEFINIRE)
#define PE_Alarm 300	//Sampling Rate Water level Alarm (DA DEFINIRE)


//Definizione Variabili
Scheduler sched;

LCD* lcd;
ServoMotor* motor;

void setup()
{
  //Componenti
  Sonar* sonar = new Sonar(SonarTrig, SonarEcho);
  LightSensor* ls = new LightSensor(LS);
  Pir* pir = new Pir(PIR);
  //Pot potentiometer = new Pot(POT);
  //button btn = new Button(8);
  motor = new ServoMotor(Motor);
  Led* pedestrianLed = new Led(ledA);
  Led* bridgeGreen = new Led(ledB);
  Led* bridgeRed = new Led(ledC);
  lcd = new LCD();
  lcd->init();

  
  //Setup
  Serial.begin(9600);

  //Tasks
  sched.init(250);

  Task* lights = new LightTask(pir, pedestrianLed, ls, TH_L);
  lights->init(500);

  Task* normalState = new State(String("Normal"), bridgeGreen, bridgeRed, sonar, motor, 1, 0, WL_1, 30, 10, 1, 0, 0);
  normalState->init(PE_Normal);

  Task* preAlarmState = new State(String("PreAlarm"), bridgeGreen, bridgeRed, sonar, motor, 1, 2000, WL_2, WL_1, 10, 1, 0, 0);
  preAlarmState->init(PE_PreAlarm);

  Task* alarmState = new State(String("Alarm"), bridgeGreen, bridgeRed, sonar, motor, 0, 1, WL_MAX, WL_2, 10, 1, 1, 180);
  alarmState->init(PE_Alarm);

  Task* StateAct = new StateActivator(normalState, preAlarmState, alarmState, lights, sonar, true, true, false);
  StateAct->init(250);

  sched.addTask(StateAct);
  sched.addTask(lights);
  sched.addTask(normalState);
  sched.addTask(preAlarmState);
  sched.addTask(alarmState);
}

void loop()
{
  sched.schedule();
  //motor->setPosition()
  //lcd->setState("Normal");
  //Serial.println(digitalRead(7));

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


/*
  if(digitalRead(7)==HIGH){
    motor->off();
  }
  //int pos=analogRead(POT);
  //while(digitalRead(7)==HIGH){
    motor->on();
    int pos = map(analogRead(A2), 0, 1023, 0, 179);
    Serial.println(pos);
    motor->setPosition(pos);     
    
    delay(30);            
    motor->off();
    lcd->setState(String(pos));
    */
  //}
  //motor->off();

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