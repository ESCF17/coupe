int pin1Moteur1=2; //pin de commande moteur 1
int pin2Moteur1=4; // pin de commande moteur 1
int pinPMoteur1=3;// pin PWM moteur 1
void setup() {
// put your setup code here, to run once:
Serial.begin(9600); //initialise la communication série
pinMode(pin1Moteur1,OUTPUT);
pinMode(pin2Moteur1,OUTPUT);
pinMode(pinPMoteur1,OUTPUT);

}

void loop() {

actionMoteur(1,1,100); //moteur 1 95% puissance sens 1
delay(2000); //attente de 0.5 secondes

actionMoteur(1,-1,100); //moteur 1 40% puissance sens 1 (Permet de maintenir la lame en haut)

delay(2000); //attente de 2 secondes
//actionMoteur(1,1,30); //moteur 1 100% puissance sens -1
//delay(2000);
//actionMoteur(1,0,0); //arrêt moteur 1
//delay(2000);

}


void actionMoteur(int moteur,int sens,int pourcentage){
  int pin1,etat1,pin2,etat2,pinP,puissance; //variable de la fonction
  //test numéro du moteur
  if (moteur==1){
    pin1=pin1Moteur1;
    pin2=pin2Moteur1;
    pinP=pinPMoteur1;
  }
  else {
  }
  //test sens du moteur 1,-1 (sens contrainre) ou tout autre valeur (stoppe le moteur)
  if (sens==1){
    etat1=1;
    etat2=0;
  }
  else if (sens==-1){
    etat1=0;
    etat2=1;
  }
  else {
    etat1=0;
    etat2=0;
  }
  puissance=map(pourcentage,0,100,0,255);
  analogWrite(pinP,puissance);
  digitalWrite(pin1,etat1);
  digitalWrite(pin2,etat2);

}

