#!/usr/bin/python

import rospy
import math
import sqlite3

from std_msgs.msg import String

def callback(data):
    rospy.loginfo('Donnee en brute %s', data.data)
    tableauAngle = data.data.split(";")
    degree2coord(int(tableauAngle[0]),int(tableauAngle[1]),int(tableauAngle[2]))
		

def degree2coord(aPara,bPara,cPara) : 
	L = 3000
	l = 2100
	pi = math.pi
	alpha = aPara * pi / 180
	beta = bPara * pi / 180
	gamma = cPara * pi / 180
	u = 3178.44
	v = 3178.44
	q = 70.71 * pi / 180
	r = 19.29 * pi / 180
	s = 19.29 * pi / 180
	t = 70.71 * pi / 180
	w = 2100
	inum = math.pow(((v / math.sin(gamma)) * math.cos(r-gamma+pi/2)+(w/math.sin(alpha))*math.cos(alpha-pi)),2)
	idenum = math.pow(((v / math.sin(gamma)) * math.cos(r - gamma + pi / 2) + (w / math.sin(alpha) * math.cos(alpha - pi))), 2) + math.pow(((v / math.sin(gamma) * math.sin(r - gamma + pi / 2) + (w / math.sin(alpha) * math.sin(alpha - pi)))), 2)
	irace = math.sqrt(inum / idenum)
	i = math.acos(irace)
	jnum = math.pow(((u / math.sin(beta)) * math.cos(s - beta + pi / 2) + (w / math.sin(alpha)) * math.cos(alpha - pi)), 2)
	jdenum = math.pow(((u / math.sin(beta)) * math.cos(s - beta + pi / 2) + (w / math.sin(alpha) * math.cos(alpha - pi))), 2) + math.pow(((u / math.sin(beta) * math.sin(s - beta + pi / 2) + (w / math.sin(alpha) * math.sin(alpha - pi)))), 2)
	jrace = math.sqrt(jnum / jdenum)
	j = math.acos(jrace)
	a = w / math.sin(alpha) * math.sin(j);
	x = a * math.cos(i)
	y = 3000 - a * math.sin(i)
	rospy.loginfo('Coordonnee stockes %d;%d', x,y)
	connectionBaseMYSQL(x,y)

def connectionBaseMYSQL(X,Y):
        conn = sqlite3.connect('base_test.db')
        c = conn.cursor()
        valX = str(X)
        valY = str(Y)
        c.execute("INSERT INTO test_coord (coordX,coordY) VALUES ("+valX+","+valY+")")
        conn.commit()
        conn.close()


def listener():
    rospy.init_node('listener_test_coord', anonymous=True)
    rospy.Subscriber('cmd_test_coord', String, callback)
    rospy.spin()

if __name__ == '__main__':
    listener()
