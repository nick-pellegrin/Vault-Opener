import serial
import time

timeout = 5

# create a serial port object for the virtual COM port
ser = serial.Serial('COM2', 9600, timeout=timeout)

# open a file for writing
with open('log.txt', 'a') as f:
    # continuously listen for incoming data on the virtual COM port
    while True:
        data = ser.readline()

        decodedString = data.decode('utf-8')

        if len(decodedString) >= 2:
            # write the data to the file
            if (data.decode('utf-8'))[1] == '*':
                f.write(decodedString[1:])

        f.flush()
        time.sleep(1)
    