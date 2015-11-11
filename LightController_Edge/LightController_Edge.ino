#include <Time.h>  

#define TIME_MSG_LEN  11   // time sync to PC is HEADER followed by Unix time_t as ten ASCII digits
#define TIME_HEADER  'T'   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 

bool lightOff;
int indicatorPin = 12;
int switchPin = 13;

// T1262347200  //noon Jan 1 2010

void setup()  {
  Serial.begin(9600);
  time_t pctime = 0;   
  setTime(pctime);
  lightOff = true;
  pinMode(switchPin, OUTPUT);
  pinMode(indicatorPin, OUTPUT);
}

void loop(){    
  digitalClockDisplay();  
  delay(1000);
}

void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
  if(hour() == 0 && lightOff == true){
    Serial.println("Begin light period");
    digitalWrite(switchPin, HIGH);
    digitalWrite(indicatorPin, LOW);
    lightOff = false;
  }else if(hour() == 16){
    Serial.println("Begin light period");
    digitalWrite(switchPin, LOW);
    digitalWrite(indicatorPin, HIGH);
    lightOff = true;
  }
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
