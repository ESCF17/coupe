//#include <ros.h>
//#include <std_msgs/String.h>

const int GO = 2;

int valeurLue = 0;

void setup() {
  Serial.begin(9600);
}

int maFonction(){
  valeurLue = digitalRead(GO);
  Serial.println(valeurLue);
  if(valeurLue == LOW){
    Serial.println("arret");
    return 0;
  } 
  else if(valeurLue == HIGH){
    Serial.println("marche");
    return 1;
  }
}

void loop() {
  int MaValeur = maFonction();
  if(MaValeur == 1){
    //p.publish(MaValeur);
    Serial.println("Valeur publie");
  }
  delay(500);
}
