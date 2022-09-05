# -*- coding:utf-8 -*-
import serial
import time
import sys
#配置串口 Configure serial port
ser = serial.Serial("/dev/ttyUSB0", 115200)
# 选择播报语句Select broadcast statement
def void_write(void_data):
    void_data1 = int(void_data/100)+48
    void_data2 = int(void_data%100/10)+48
    void_data3 = int(void_data%10)+48
    cmd = [0x24, 0x41, void_data1, void_data2, void_data3, 0x23]
    #print(cmd)
    ser.write(cmd)
    time.sleep(0.005)
    #ser.flushInput()

# 读取识别的语音 Read recognized speech
def speech_read():
    count = ser.inWaiting()
    if count:
        speech_data = ser.read(count)
        speech_data1 = int(str(speech_data)[4:5])
        speech_data2 = int(str(speech_data)[5:6])
        speech_data3 = int(str(speech_data)[6:7])
        ser.flushInput()
        time.sleep(0.005)
        return int(speech_data1*100+speech_data2*10+speech_data3) 
    else:
        return 999


if ser.isOpen():
    print("Speech Serial Opened! Baudrate=115200")
else:
    print("Speech Serial Open Failed!")

try:
    while True:
        speech_r = speech_read()
        if speech_r != 999:
            if speech_r == 0:
                print("hi")
            elif speech_r == 10:
                print("OK")
                time.sleep(0.1)
                void_write(10)
except KeyboardInterrupt:
    ser.close()
    print("Close!")