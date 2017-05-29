#include <Servo.h>

Servo myservo;
int pos = 100;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(100);
}

void loop() {

  if (Serial.available() > 0) {
    String var = Serial.readString();
    Serial.println("RECU");

    if (var == "1") //rentrer 1 dans la console pour executer
    {

      for (pos = 100; pos >= 1; pos -= 1)
      {
        myservo.write(pos);
        delay(5);
      }
      for (pos = 1; pos <= 100; pos += 1)
      {
        myservo.write(pos);
        delay(15);
      }

      Serial.println("TERMINE");
    }
  }
}
