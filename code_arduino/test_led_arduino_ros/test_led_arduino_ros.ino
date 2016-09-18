#include <ros.h>
#include <std_msgs/Int8.h>

int led = 8;
bool etat  = false;


void etatLed(const std_msgs::Int8& ard_cmd){
  Serial.print("Message ROS : ");
  Serial.println(ard_cmd.data);
  if(ard_cmd.data == 1){
    etat = !etat;
    if(etat){
      digitalWrite(led,HIGH);
    }else{
      digitalWrite(led,LOW);
    }
  }
  
}

ros::NodeHandle nh;
ros::Subscriber<std_msgs::Int8> sub("chatter",etatLed);

void setup() {
  // put your setup code here, to run once:
   pinMode(led,OUTPUT);
   Serial.begin(9600);
 

   nh.getHardware()->setBaud(9600);
   nh.initNode();
   nh.subscribe(sub);
   delay(200);
}

void loop() {
  // put your main code here, to run repeatedly:
  nh.spinOnce();
  delay(100);
  
}
