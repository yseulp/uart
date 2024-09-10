import serial
import time
import random
import string

with serial.Serial('/dev/ttyS0', 9600) as ser:
    print(ser.readline()) #read hello blocking to wait for uC to be ready
    i = 0
    while True:
        ser.write(f"{i}".encode())
        recv = ser.read(1).decode("utf-8")
        print(recv, end="", flush=True)
        assert(int(recv) == i)
        i = (i + 1) % 10