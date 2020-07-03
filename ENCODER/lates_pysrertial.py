from textwrap import wrap
import serial
import numpy as np
import random 
import time
import string

ser = serial.Serial(
    port='COM6',
    baudrate=9600,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS )

samples =15
ser.isOpen
inputData1 = []

for x in range(samples):
   inputData1.append(random.randint(0,255))
   

for i in range(len(inputData1)):
    X = '{:03d}'.format(inputData1[i])
    data = str(X).encode('utf-8')
    ser.write(data) 
    time.sleep(1)
    
    
ser.close()

print("Data sent")
[print(x) for x in inputData1]
################################################
#ser = serial.Serial(
#    port='COM6',
#    baudrate=9600,
#    stopbits=serial.STOPBITS_ONE,
#    bytesize=serial.EIGHTBITS )
#
#ser.isOpen
#
#seq = [0]*samples
#count = 1
#joined=[]
#
#while (count <= samples-1):
#    for c in ser.read():
#        seq[count-1]=(chr(c)) #convert from ANSII
#       # joined_seq = ''.join(str(v) for v in seq)       
#        count = count + 1
#        
#     
#ser.close()
#print("Data Received")
##[print(x) for x in inputData1]