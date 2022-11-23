#ifndef __SONAR__
#define __SONAR__

class Sonar { 
  
public:
  Sonar(int trigPin, int echoPin);
  float MeasureDistance();
  float getLastDistance();
private:
  int trigPin;  
  int echoPin; 
  float lastDistance;
  double vs;
};



#endif