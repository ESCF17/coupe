//#include <ros.h>
//#include <std_msgs/String.h>

const int entrer = 2;
const int GO = 1 ;

int valeurLue = 0;

void setup() {
  Serial.begin(9600);
}

int maFonction(){
  digitalWrite(entrer,HIGH);
  valeurLue = analogRead(GO);
  Serial.println(valeurLue);
  if(valeurLue < 1000){
    Serial.println("arret");
    return 0;
  } 
  else{
    return 1;
  }
}

void loop() {
  int MaValeur = maFonction();
  if(MaValeur == 0){
    //p.publish(MaValeur);
    Serial.println("Valeur publie");
  }
  delay(500);
}
