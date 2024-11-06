#include <ESP32Servo.h>

Servo driveMotor;
int drivePin = 25;

int value; //rename later


void setup() {
  Serial.begin(9600);
  
  driveMotor.attach(drivePin, 1000, 2000);

}

void loop() {
  
   value = analogRead(27);//0 to 100
   
  
  value = map(value, 0, 1023, 0, 180);
  Serial.println(value);

  driveMotor.write(value);

}
