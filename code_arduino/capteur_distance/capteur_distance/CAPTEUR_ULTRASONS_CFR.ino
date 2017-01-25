//CAPTEUR NORD
int TRIGGERCAPTEURNORD=2;
int ECHOCAPTEURNORD=3;
float DISTANCE_NORD=0;
float LECTURE_ECHO_NORD=0;

//Capteur SUD
int TRIGGERCAPTEURSUD=11;
int ECHOCAPTEURSUD=10;
float DISTANCE_SUD=0;
float LECTURE_ECHO_SUD=0;

void setup() {
  //CAPTEUR NORD
  pinMode(TRIGGERCAPTEURNORD,OUTPUT);
  pinMode(ECHOCAPTEURNORD,INPUT);
  
  //CAPTEUR SUD
  pinMode(TRIGGERCAPTEURSUD,OUTPUT);
  pinMode(ECHOCAPTEURSUD,INPUT);
  
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  CAPTEUR_POUR_ROS();
  delay(500);
 
}
float CAPTEURNORD()
{
  digitalWrite(TRIGGERCAPTEURNORD,HIGH);
  delay(10);
  digitalWrite(TRIGGERCAPTEURNORD,LOW);
  LECTURE_ECHO_NORD=pulseIn(ECHOCAPTEURNORD,HIGH);
  DISTANCE_NORD= LECTURE_ECHO_NORD/58;
  DISTANCE_NORD = DISTANCE_NORD*10;
  //Serial.print("Distance NORD : " + (String)DISTANCE_NORD);
  //Serial.println("");
  return DISTANCE_NORD;
}
float CAPTEURSUD()
{
  digitalWrite(TRIGGERCAPTEURSUD,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGERCAPTEURSUD,LOW);
  LECTURE_ECHO_SUD = pulseIn(ECHOCAPTEURSUD,HIGH);
  DISTANCE_SUD = LECTURE_ECHO_SUD/58;
  DISTANCE_SUD = DISTANCE_SUD *10;
  //Serial.print("S:" + (String)DISTANCE_SUD);
  //Serial.println("");
  return DISTANCE_SUD;
}
void CAPTEUR_POUR_ROS()
{
  float nord = CAPTEURNORD();
  float sud = CAPTEURSUD();
  Serial.print("N" + (String)nord + "S"+ (String)sud);
  Serial.println("");
}

