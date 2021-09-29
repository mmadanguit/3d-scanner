/*
 * moves both servos for the two servo scan and relays the servo angles and distance readings to python
 */

#include <Servo.h>

Servo xServo;  // create servo object for the servo controlling panning
Servo yServo;  // create servo object for the servo controlling tilting
int xPos = 0;  // variable to store the xServo position
int yPos = 10;  // variable to store the yServo position

const int analogInPin = A0;  // analog input pin the distance sensor is attached to
int sensorValue = 0;  // variable to store the value coming from the distance sensor

/*
 * setup function to initialize hardware and software
 */
void setup() { 
  Serial.begin(9600);  // start the serial port 
  xServo.attach(9);  // attach the servo on pin 9 to the horizontal servo object
  yServo.attach(8);  // attach the servo on pin 10 to the vertical servo object
}

/*
 * main loop
 */
void loop() {  
  for (yPos = 10; yPos <= 65; yPos += 5) {  // yServo sweep throught of 10 to 65 degree
    yServo.write(yPos);
    for (xPos = 20; xPos <= 80; xPos+= 3) {  // xServo sweeps through 20 to 80 degrees
      xServo.write(xPos); 
      sensorValue = analogRead(analogInPin);

      // transmit one line of text to python with distance reading and sensor positions
      Serial.print(sensorValue);  Serial.print(",");  
      Serial.print(xPos);  Serial.print(",");  
      Serial.println(yPos);
      
      delay(400);  // delay after sending data so the serial connection is not over run
    }
    xPos = 0;
    delay(500);  // delay after sending data so the servo can reach its position
  }
}
