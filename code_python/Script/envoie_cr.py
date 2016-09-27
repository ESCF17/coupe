#!/usr/bin/env python
# -*- coding: utf-8 -*-

import csv
import smtplib
from email.MIMEMultipart import MIMEMultipart
from email.MIMEText import MIMEText


class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


firstRead = True

def stringToEnum(chaine) : 
	index = 0
	result = ""
	result_tab = chaine.split('-')
	if(len(result_tab) > 1):
		for i in range(1,len(result_tab)):
			result += str(i)+") "+result_tab[i].strip()+"\n"
	else : 
		result = "1) "+chaine+"\n"
	return result

## Connection au serveur de google 
fromaddr = "cr.davincibot.cfr@gmail.com"
msg = MIMEMultipart()
server = smtplib.SMTP('smtp.gmail.com', 587)
server.starttls()
server.login(fromaddr, "DaVinciBo")

## Demande la date de la réunion
print("Donner la date de la reunion (dd/mm) :")
date = raw_input()



## A chaque ligne on envoie un email
with open('test_to_do.csv') as csvfile:
    reader = csv.DictReader(csvfile)
    for row in reader:
	if(firstRead):
		recap = stringToEnum(row['recap'])
		date_next = row['date_next']
		firstRead = False	
		
	msg = MIMEMultipart()
	msg['From'] = fromaddr
	toaddr = row['adresse'] 
	msg['Subject'] = "[CFR][BOT-CR] "+ row['nom'].split(" ")[0]
	msg['To'] = toaddr
	body ="---------------------------------- \nCompte rendu de la réunion du "+date+" :\n----------------------------------\n + Récap général de la réunion : \n"+ recap +"\n + Travail individuel à faire : \n"+ stringToEnum(row['to_do'])+"\n + Prochaine réunion :\n"+ date_next
	body += "\n\n----------------- \nMail envoyé par un bot, \nMERCI DE NE PAS REPONDRE A CE MAIL !\nDaVinciBot.\n----------------- "	
	print("Envoie du mail à "+bcolors.OKGREEN+row['nom'].upper()+bcolors.ENDC+" à l'adresse : "+bcolors.OKGREEN+toaddr.upper()+bcolors.ENDC)
	print(body+"\n\n\n")
	msg.attach(MIMEText(body, 'plain',"utf-8"))
	text = msg.as_string()
	server.sendmail(fromaddr, toaddr, text)
server.quit()



		
	

