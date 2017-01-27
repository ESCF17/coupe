//#include <ros.h>
//#include <std_msgs/String.h>

//MONTAGE AVEC RESISTANCE DE 10 KOHM

const int GO = 2;

int valeurLue = 0;

void setup() {
  Serial.begin(9600);
}

int maFonction(){ //Cette fonction renvoie si le fils est encore sur le montage ou pas
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
  if(MaValeur == 1){ //Si le fils n'est plus sur le montage il renvoie "marche", ce qui veut dire que le robot doit commencer
    //p.publish(MaValeur);
    Serial.println("Valeur publie");
  }
  delay(500);
}
