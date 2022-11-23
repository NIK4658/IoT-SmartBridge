#include "Sonar.h"
#include "Arduino.h"

Sonar::Sonar(int trigPin, int echoPin){
  this->trigPin = trigPin;
  this->echoPin = echoPin;
  this->lastDistance = 0;
  this->vs = 331.45 + 0.62*20;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

float Sonar::MeasureDistance(){
  /* invio impulso */
  digitalWrite(trigPin,LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin,LOW);
   
  /* ricevi l’eco */
  long tUS = pulseInLong(echoPin, HIGH);
  double t = tUS / 1000.0 / 1000.0 / 2;
  double d = t*vs;
  this->lastDistance=d;
  return d;
}

float Sonar::getLastDistance(){
  return this->lastDistance;
};
