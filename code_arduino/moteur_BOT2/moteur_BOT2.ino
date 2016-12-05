#define STOP 0 
#define AV   1 
#define AR   2 

#include <ros.h>
#include <std_msgs/String.h>



void moteur1(int param,int vitesse){    //Gauche
  if (param == STOP){
    digitalWrite(9,LOW);    digitalWrite(10,LOW);    analogWrite(3,0);
  }
  else{
    analogWrite(3,vitesse);
  }
  if (param == AV){
    digitalWrite(9,LOW);   digitalWrite(10,HIGH);
    
  }
  if (param == AR){
    digitalWrite(9,HIGH);  digitalWrite(10,LOW);
  }
}

void moteur2(int param, int vitesse){   //Droit
  if (param == STOP){
    digitalWrite(2,LOW);    digitalWrite(6,LOW);    analogWrite(5,0);
  }
  else{
    analogWrite(5,vitesse);
  }
  if (param == AV){
    digitalWrite(2,LOW);   digitalWrite(6,HIGH);
  }
  if (param == AR){
    
    digitalWrite(2,HIGH);  digitalWrite(6,LOW);
  }
}


void motor_control( const std_msgs::String& ard_cmd){
  Serial.print(ard_cmd.data);
  if(ard_cmd.data[0] == 'q'){ moteur1(AV,150);    moteur2(AV,150);    }
  if(ard_cmd.data[0] == 'd'){ moteur1(AR,150);    moteur2(AR,150);    }
  if(ard_cmd.data[0] == 's'){ moteur1(AV,150);    moteur2(AR,150);    }
  if(ard_cmd.data[0] == 'z'){ moteur1(AR,150);    moteur2(AV,150);    }
  if(ard_cmd.data[0] == 'a'){ moteur1(STOP,0);    moteur2(STOP,0);    }
}

ros::NodeHandle  nh;
ros::Subscriber<std_msgs::String> sub("cmd_key_arduino" , motor_control);


void setup()
{
  nh.getHardware()->setBaud(57600);
  pinMode(9,OUTPUT);  pinMode(10,OUTPUT); pinMode(3,OUTPUT);
  pinMode(2,OUTPUT);  pinMode(6,OUTPUT);  pinMode(5,OUTPUT);
  Serial.begin(57600);
  nh.initNode();
  nh.subscribe(sub);
  delay(200);
}

void loop()
{
  nh.spinOnce();
  delay(100);
}
