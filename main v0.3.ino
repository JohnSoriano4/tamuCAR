/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

float light = A0;
int delayPin = A1;
int curve = A2;
float volt = 0;
int motor = A3;

int minTime = 1000;
int maxTime = 25000;
int delayTime = 0;
int delayTime2 = 0;

float minPower = 0.1;
float maxPower = 2;
float Power = 0;
int powerRead = 0;
float countdown = 0;

float motorOutput = 0;
int OFF = 0;

void setup() {
  Serial.begin(9600);
  pinMode(light, INPUT);
  pinMode(delayPin, INPUT);
  pinMode(curve, INPUT);
  pinMode(motor, OUTPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("initializing");
  delay(1000);


  delayTime = analogRead(delayPin);
  delayTime2 = (((maxTime - minTime) / 1024) * delayTime);
  //Serial.println("delay");
  //Serial.println(delayTime2);
  lcd.clear();
  lcd.print(OFF);

  powerRead = analogRead(curve);
  Power = (((maxPower - minPower) / 1024) * powerRead);
  //Serial.println(powerRead);
  //Serial.println("power");
  //Serial.println(Power);
  lcd.setCursor(0,1);
  lcd.print(Power);
  delay(1000);

}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  volt = analogRead(light);
  lcd.setCursor(0,0);
  lcd.print("volt");
  lcd.setCursor(0,5);
  lcd.print(volt);

  if (volt < 3){
    lcd.setCursor(0,0);
    lcd.print("volt");
    lcd.setCursor(0,5);
    lcd.print(volt);
    delay(200);
    OFF = 2000;
  }


  while (OFF = 2000) {
    lcd.setCursor(0,0);
    lcd.print("volt");
    lcd.setCursor(0,5);
    lcd.print(volt);
      if (volt > 10);
        lcd.setCursor(0,0);
        lcd.print("volt");
        lcd.setCursor(0,5);
        lcd.print(volt);
        motorOutput = pow(1.1, 40 - (Power * countdown));
        countdown = countdown + 1;
        lcd.setCursor(0,1);
        lcd.print("motor");
        lcd.setCursor(7,1);
        lcd.print(motorOutput);
        //Serial.println("motor");
        //Serial.println(motorOutput);
        delay(500);
        if (motorOutput < 0.01) {
          while (1){
          lcd.setCursor(0,0);
          lcd.print("motor stopped");
        }
      }
    }
}

  
