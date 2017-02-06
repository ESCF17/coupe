#include <Servo.h>

Servo myservo; 
int pos = 0;   

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  
}

void loop() {
  pos = 100;
  if (Serial.available() > 0) {
    String var = Serial.readString();
    if (var == "1") //rentrer 1 dans la console pour executer
    {
      for (pos = 100; pos >= 40; pos -= 1) 
      {
        myservo.write(pos);              
        delay(5);                  
      }
      
      for (pos = 40; pos <= 100; pos += 1) 
      { 
        // in steps of 1 degree
        myservo.write(pos);              
        delay(15);                  
      }
    }
  }
}

