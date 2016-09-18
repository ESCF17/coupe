#include <ros.h>
#include <std_msgs/String.h>


int button = 7;
int led = 8;


ros::NodeHandle nh;
std_msgs::String str_msg;
ros::Publisher chatter("test_coord", &str_msg);

void setup() {

  pinMode(button,INPUT);
  pinMode(led,OUTPUT);

  nh.getHardware()->setBaud(9600);
  nh.initNode();
  nh.advertise(chatter);

  Serial.begin(9600);
}

void loop(){
  if(digitalRead(button) == 1){
    digitalWrite(led,HIGH);
    long alpha = (random(1,181));  
    long beta = (random(1,271));
    long gamma = 360 - (alpha + beta);
    Serial.print(alpha);
    Serial.print(" ");
    Serial.print(beta);
    Serial.print(" ");
    Serial.print(gamma);
    Serial.print(" ");
    String sendRos = String(alpha)+";"+String(beta)+";"+String(gamma);
    char charBuf[sendRos.length()+1];
    sendRos.toCharArray(charBuf,sendRos.length()+1);
    str_msg.data = charBuf;
    chatter.publish(&str_msg);
    nh.spinOnce();
  }else{
    digitalWrite(led,LOW);
  }
  delay(300);
}
