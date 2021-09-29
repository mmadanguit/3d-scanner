"""converts distance sensor readings into inches and outputs distance with servo values to a csv file"""

import serial
import math
import numpy as np
import pandas as pd

# set the name of the serial port.  Determine the name as follows:
arduinoComPort = "/dev/cu.usbmodem14201"

# set the baud rate so that it is the same as the sending program
baudRate = 9600

# open the serial port
serialPort = serial.Serial(arduinoComPort, baudRate, timeout=1)

# initialize lists to store r and theta values
r = []
x_theta = []
y_theta = []

def find_distance(sensorValue):
    """convert distance sensor value into distance based on calibration function"""
    f = [0.2131, -21.019, 598.78-sensorValue]
    roots = np.roots(f)
    return roots[1].real

# main loop to read data from the Arduino
while True:

    # ask for a line of data from the serial port, the ".decode()" converts the data from an "array of bytes", to a string
    lineOfData = serialPort.readline().decode()

    # check if data was received
    if len(lineOfData) > 0:
        # data was received, convert it into respective variables
        sensorValue, xPos, yPos = (int(x) for x in lineOfData.split(','))

        # convert distance sensor value into distance in inches
        dist = find_distance(sensorValue)+2.5

        # append values to x and y matrices
        r.append(dist)
        x_theta.append(xPos)
        y_theta.append(yPos)

        # check if scan is done
        if yPos == 65:
            break

# convert lists into arrays
r_array = np.asarray(r)
r_array = np.reshape(r_array, (r_array.size, 1))
xtheta_array = np.asarray(x_theta)
xtheta_array = np.reshape(xtheta_array, (xtheta_array.size, 1))
ytheta_array = np.asarray(y_theta)
ytheta_array = np.reshape(ytheta_array, (ytheta_array.size, 1))
rtheta_array = np.concatenate((r_array, xtheta_array, ytheta_array), axis=1)

# save final array as csv file
pd.DataFrame(rtheta_array).to_csv('data.csv')
