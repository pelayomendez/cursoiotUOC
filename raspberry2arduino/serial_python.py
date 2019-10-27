#
# Recive ON / OFF commands from serial on MKR1000 and light inner LED
# UOC iOT
# Pelayo Méndez 
#
# Python3 test serial communication interface
# Depends on pyserial (pip3 install pyserial)

from serial import Serial
import time

ser = Serial('/dev/ttyACM0',9600)

if ser.isOpen():
     print(ser.name + ' is open...')

while True:
	cmd = input("Enter command or 'exit':")
	if cmd == 'exit':
		ser.close()
		exit()
	else:
		if (len(cmd)>0):
			ser.write(cmd.encode())
		else:
			continue
	
	out = ser.readline()
	print('Echo...' + str(out))

