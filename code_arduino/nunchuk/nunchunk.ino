#include <Wire.h>
#include <ros.h>
#include <std_msgs/String.h>


// Doit être ajusté en fonction de chaque nunchuck
#define ZEROX 530
#define ZEROY 530
#define ZEROZ 530

// adresse I2C du nunchuck
#define WII_NUNCHUK_I2C_ADDRESS 0x52

// définition d'une variable counter
int counter;
double refX = -1;
double refY = -1; 
double refZ = -1;

// définition d'un tableau de données
uint8_t data[6];
String lastResult = "";
ros::NodeHandle nh;
std_msgs::String test;
ros::Publisher p("cmd_key_arduino", &test);


void setup()
{
nh.getHardware()->setBaud(57600);
nh.initNode();
nh.advertise(p);
//initialisation du nunchuck
Wire.begin();

Wire.beginTransmission(WII_NUNCHUK_I2C_ADDRESS);
Wire.write(0xF0);
Wire.write(0x55);
Wire.endTransmission();

Wire.beginTransmission(WII_NUNCHUK_I2C_ADDRESS);
Wire.write(0xFB);
Wire.write(0x00);
Wire.endTransmission();
}



void loop()
{
// on demande 6 octets au nunchuck
Wire.requestFrom(WII_NUNCHUK_I2C_ADDRESS, 6);

counter = 0;
// tant qu'il y a des données
while(Wire.available())
{
// on récupère les données
data[counter++] = Wire.read();
}

// on réinitialise le nunchuck pour la prochaine demande
Wire.beginTransmission(WII_NUNCHUK_I2C_ADDRESS);
Wire.write(0x00);
Wire.endTransmission();

double accelX = ((data[2] << 2) + ((data[5] >> 2) & 0x03) - ZEROX);
double accelY = ((data[3] << 2) + ((data[5] >> 4) & 0x03) - ZEROY);
double accelZ = ((data[4] << 2) + ((data[5] >> 6) & 0x03) - ZEROZ);

if(refX == -1 && accelX != -ZEROX){
   refX = accelX;
   refY = accelY;
   refZ = accelZ;
}

// on extrait les données
// dans mon exemple j'utilise uniquement les données d'accélération sur l'axe Y


// on limite la valeur entre -180 et 180
char result = ' ';
if(refX - accelX > 100){
 // Serial.println("gauche");
  result = 'q';
}else if(refX - accelX  < -100){
  //Serial.println("droite");
  result = 'd';
}else if(refY - accelY  > 100){
  //Serial.println("deriere");
  result = 's';
}else if(refY - accelY < -100){
  //Serial.println("devant");
  result = 'z';
}else{
  //Serial.println("stop");
  result = 'a';
}

//String chaine = String(refX-accelX)+"%"+String(refY-accelY)+"%"+String(refZ-accelZ);
//Serial.println(chaine);
if(!lastResult.equals(result)){
  lastResult = result;
  test.data = &result;
  p.publish(&test);
  nh.spinOnce();
}

// on écrit sur le servomoteur la valeur

// un petit delai pour pas saturer le servomoteur
delay(100);

}
