/*
 * moves one servo and relays the servo angle and distance sensor reading to python
 */

#include <Servo.h>

Servo xServo;  // create servo object for the servo controlling panning
Servo yServo;  // create servo object for the servo controlling tilting
int xPos = 0;  // variable to store the xServo position

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
  yServo.write(45);  // yServo goes to 45 degrees
  for (xPos = 20; xPos <= 80; xPos+= 3) {  // xServo sweeps through 20 to 80 degrees
    xServo.write(xPos); 
    sensorValue = analogRead(analogInPin);

    // transmit one line of text to python with distance reading and sensor position
    Serial.print(sensorValue);  Serial.print(","); 
    Serial.println(xPos);  
    
    delay(400);  // delay after sending data so the serial connection is not over run
  }
}
