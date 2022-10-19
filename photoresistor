
#include <LiquidCrystal.h>

//LCD screen operating in 4 bit mode

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//initialize pin A0 for analog input
//initialize volt variable

int analogPin = A0;
int volt = 0;

void setup() {
  Serial.begin(9600);
  pinMode(analogPin, INPUT);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("chem e car");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  // loop analog read (scale from 0-1023) from photoresistor
  lcd.setCursor(0, 1);
  volt = analogRead(analogPin);
  lcd.print(volt * 100);
  Serial.println(volt);
  delay(500);
}

