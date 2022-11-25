//Montanari Nicola

#include "Scheduler.h"
#include "Task.h"
#include "Led.h"
#include "State.h"
#include "Sonar.h"
#include "StateActivator.h"
#include "Pir.h"
#include "LightSensor.h"
#include "ServoTimer2.h"
#include "LCD.h"
#include "LightTask.h"
#include "ServoTimer2.h"
#include "Potentiometer.h"
#include "Button.h"
#include "MsgService.h"

//Definizioni PINS

#define ledA 2 	//Green for lightning
#define ledB 3 	//Green for bridge status
#define ledC 4 	//Red for alarm state

#define LS A0 	      //Light Sensor
#define PIR 5 	      //PIR
#define POT A2 	      //Valve controller
#define BTN 7 	      //Manual mode
#define SonarTrig 13  //Sonar trig
#define SonarEcho 12  //Sonar echo
#define Motor 9       //Servo Motor (Valve)

//Definizioni Costanti

#define TH_L 400      //Light Treshold
#define T1 5000       //Tempo da tenere accese le luci dopo la rilevazione dei pedoni

//DISTANZA DALL'ACQUA
#define WL_1 0.75	    //Water distance: Normal 
#define WL_2 0.5	    //Water distance: Pre alarm 
#define WL_MAX 0.01	  //Water distance: Alarm 
#define WL_MIN 30	    //MAX Water distance. (Fiume in secca).

#define PE_Normal 2000 	      //Sampling Rate Water level Normal 
#define PE_PreAlarm 1000	    //Sampling Rate Water level PreAlarm 
#define PE_Alarm 750	        //Sampling Rate Water level Alarm
#define PE_Lights 500	        //Rate Smart Lights 
#define PE_StateActivator 250	//Rate StateActivator

#define PE_Scheduler 250      //Rate Scheduler


//Definizione Variabili
Scheduler sched;

void setup()
{
  //Setup
  Serial.begin(9600);
  MsgService.init();

  //Componenti
  Sonar* sonar = new Sonar(SonarTrig, SonarEcho);
  LightSensor* ls = new LightSensor(LS);
  Pir* pir = new Pir(PIR);
  Potentiometer* pot = new Potentiometer(POT);
  Button* btn = new Button(BTN);
  ServoTimer2* motor = new ServoTimer2();
  motor->attach(Motor);
  Led* pedestrianLed = new Led(ledA);
  Led* bridgeGreen = new Led(ledB);
  Led* bridgeRed = new Led(ledC);
  LCD* lcd = new LCD();
  lcd->init();

  //Tasks
  sched.init(PE_Scheduler);

  Task* lights = new LightTask(pir, pedestrianLed, ls, TH_L, T1);
  lights->init(PE_Lights);

  Task* normalState = new State(String("Normal"), bridgeGreen, bridgeRed, sonar, motor, lcd, pot, btn, LCDState::DISABLED, 1, 0, WL_1, WL_MIN, WL_MIN, false, 0, 0);
  normalState->init(PE_Normal);

  Task* preAlarmState = new State(String("PreAlarm"), bridgeGreen, bridgeRed, sonar, motor, lcd, pot, btn, LCDState::ENABLED, 1, 2000, WL_2, WL_1, WL_MIN, false, 0, 0);
  preAlarmState->init(PE_PreAlarm);

  Task* alarmState = new State(String("Alarm"), bridgeGreen, bridgeRed, sonar, motor, lcd, pot, btn, LCDState::ENABLED_WITHVALVE, 0, 1, WL_MAX, WL_2, WL_MIN, true, 1, 180);
  alarmState->init(PE_Alarm);

  Task* StateAct = new StateActivator(normalState, preAlarmState, alarmState, lights, sonar, true, true, false);
  StateAct->init(PE_StateActivator);

  //Aggiunta task allo scheduler.
  sched.addTask(StateAct);
  sched.addTask(lights);
  sched.addTask(normalState);
  sched.addTask(preAlarmState);
  sched.addTask(alarmState);
}

void loop() 
{
  sched.schedule();
}