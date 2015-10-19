#include <Time.h>  

int relay = 13;              // Tells Arduino the relay is connected to pin 13
#define CDS_INPUT 0

//to make the loop stateful...
int lightControlStatus = 0; //0 = off, 1 = on
int lightSensorStatus = 0;

//delay times -- in seconds
int sensorDelay = 1;
unsigned int secondsOfLight = 57600; //16 * 60 * 60
unsigned int lengthOfDay = 86400; //24 * 60 * 60


void setup() 
{ 
  pinMode(relay, OUTPUT);
  Serial.begin(9600);
  lightControl(lightControlStatus); //turn the light on to start
}

void loop()                  // Loops forever
{
  time_t t = now();
  if(t >= lengthOfDay){
    setTime(0);
    lightControl(lightControlStatus);
  }
  else if(t >= secondsOfLight){
    lightControl(lightControlStatus);
  }
  if(t % sensorDelay == 0){
    lightSensor(lightSensorStatus);
  }
  delay(1000); //delay it for a second just to give it a break
}

void lightControl(int currStatus){
  switch(currStatus){
    case 0: digitalWrite(relay, HIGH);
      lightControlStatus = 1;
      break;
    case 1: digitalWrite(relay, LOW);
      lightControlStatus = 0;
      break;
  }
}

void lightSensor(int currStatus){
  switch(currStatus){
    case 0: int value = analogRead(CDS_INPUT);
      Serial.println(value);
      break;
  }
}
