#include <ESP32Servo.h>

Servo driveMotor;
int drivePin = 25;

int senseVal;
int thisSense = 0;
int lastSense = 0;
int lasterSense = 0;
int value = 0; //rename later
bool start = false;

void setup() {
  Serial.begin(9600);
  value = 0;

  delay(10000);
  driveMotor.attach(drivePin, 1000, 2000);

}

void loop() {
  /*
  value = analogRead(27);//0 to 4095
  
  value = map(value, 0, 4095 * 2, 0, 180);
  Serial.println(value / 1.80);
  */
  thisSense = analogRead(27);
  senseVal = (thisSense + lastSense + lasterSense) / 3;
  start = senseVal > 2000;

  if (start)
  {
    value = 14;
  }
  else
  {
    value = 0;
  }

  lasterSense = lastSense;
  lastSense = thisSense;
  value = map(value, 0, 100, 0, 180);
  Serial.println(value / 1.8);

  driveMotor.write(value);
  delay(100);
}
