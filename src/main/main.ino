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

#define PE_Normal 1000 	//Sampling Rate Water level Normal (DA DEFINIRE)
#define PE_PreAlarm 750	//Sampling Rate Water level PreAlarm (DA DEFINIRE)
#define PE_Alarm 500	//Sampling Rate Water level Alarm (DA DEFINIRE)


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
ServoMotor* motor;
int pos;
int delta;

void setup()
{
  Serial.begin(9600);
  sched.init(100);

  //Task* lights = new LightTask(pin);
  //lights->init(500);

  green = new Led(3);
  red = new Led(4);

  sonar = new Sonar(9,8);


  normalState = new State(green, red, sonar, 0, 0, 0, 0.1, 10, 1);
  normalState->init(PE_Normal);

  preAlarmState = new State(green, red, sonar, 0, 1, 0.1, 0.2, 10, 1);
  preAlarmState->init(PE_PreAlarm);

  alarmState = new State(green, red, sonar, 1, 1, 0.2, 30, 10, 1);
  alarmState->init(PE_Alarm);



  Task* StateActivatorr = new StateActivator(normalState, preAlarmState, alarmState, sonar);
  StateActivatorr->init(100);

  //sched.addTask(lights);
  //sched.addTask(StateActivatorr);
  //sched.addTask(normalState);
  //sched.addTask(preAlarmState);
  //sched.addTask(alarmState);

  ls = new LightSensor(A0);
  pir = new Pir(8);

  motor = new ServoMotor(A1);

  pos = 0;
  delta = 1;
  
}

void loop()
{
  //sched.schedule();

  delay(150);

  motor->on();
  for (int i = 0; i < 180; i++) {
    Serial.println(pos);
    motor->setPosition(pos);         
    // delay(2);            
    pos += delta;
  }
  motor->off();
  pos -= delta;
  delta = -delta;
  delay(1000);


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