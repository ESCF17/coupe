int dirPin1 = 3;
int stepperPin1 = 2;
int dirPin2 = 7;
int stepperPin2 = 6;
const int bouton = 1 ;
const int entrer = 8;
int valeurLue = 0;

void setup() {
  pinMode(dirPin1, OUTPUT);
  pinMode(stepperPin1, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(stepperPin2, OUTPUT);
  pinMode(bouton, INPUT);
  Serial.begin(9600);
}

void step(boolean dir, int steps) {
  digitalWrite(dirPin1, dir);
  digitalWrite(dirPin2, dir);
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepperPin1, HIGH);
    digitalWrite(stepperPin2, HIGH);
    delayMicroseconds(200);
    digitalWrite(stepperPin1, LOW);
    digitalWrite(stepperPin2, LOW);
    delayMicroseconds(200);
  }
}



int cmpte(int x) {
  int cmpt = 0;
  while (x == 1) {
    
    if(cmpt == 200){
      cmpt = 0;
    }
    
    cmpt = cmpt + 1;
    step(true, 1);
    
    valeurLue = analogRead(bouton);
    
    if(valeurLue < 1000){
      x = 1;
    }
    else{
      x = 0;
    }
    
  }
  return cmpt;
}

void loop() {
  digitalWrite(entrer, HIGH);
  int cmpt = cmpte(1);
  int result = cmpt*1.8;
  Serial.println(result + 50);
  delay(20000);
}
