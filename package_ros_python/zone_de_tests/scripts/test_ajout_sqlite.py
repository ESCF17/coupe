#!/usr/bin/python

import rospy
import sqlite3

from std_msgs.msg import Int8



def talker():
    pub = rospy.Publisher('chatter', Int8, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(2) # 10hz
    somme = 0;
    while not rospy.is_shutdown():
        hello_str = somme % 10 # % rospy.get_time()
        somme = somme + 1
	rospy.loginfo(hello_str)
        pub.publish(hello_str)
        rate.sleep()


def connectionBaseMYSQL():
	conn = sqlite3.connect('base_test.db')
	c = conn.cursor()
	valX = "12"
	valY = "16"
	c.execute("INSERT INTO test_coord (coordX,coordY) VALUES ("+valX+","+valY+")")
	conn.commit()
	conn.close()



if __name__ == '__main__':
    try:
    	connectionBaseMYSQL()
    except rospy.ROSInterruptException:
        pass


