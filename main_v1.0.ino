#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Initialize analog pins for photoresistors
int light1 = A1;
int light2 = A2;
int light3 = A3;
float photo1 = analogRead(light1);
float photo2 = analogRead(light2);
float photo3 = analogRead(light3);

//outputs
int motor = 6;
int reset = 7;

//variables
int off1 = 0;
int off2 = 0;
int off3 = 0;
int offTotal = 0;
bool trigger = true;


void setup() {
  Serial.begin(9600);
  pinMode(light1, INPUT);
  pinMode(light2, INPUT);
  pinMode(light3, INPUT);

  pinMode(reset, INPUT);
  pinMode(motor, OUTPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("initializing");
  delay(2000);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.clear();
  lcd.setCursor(0,0);
  
  digitalWrite(motor, HIGH);

  //check photoresistors
  if (photo1 < 50) {
    off1 = 1;
  }  else {
    off1 = 0;
  }

  if (photo2 < 50) {
    off2 = 1;
  }  else {
    off2 = 0;
  }

    if (photo3 < 50) {
    off3 = 1;
  }  else {
    off3 = 0;
  }
  offTotal = off1 + off2 + off3;

  lcd.print("LITE");
  lcd.setCursor(0, 5);
  lcd.print(off1);
  lcd.setCursor(0,9);
  lcd.print(off2);
  lcd.setCursor(0,13);
  lcd.print(off3);
  lcd.setCursor(0,1);
  lcd.print("MOTOR OPERATING");

  if (offTotal > 1) {
    while(true) {
      digitalWrite(motor, LOW);
      lcd.setCursor(0,0);
      lcd.print("MOTOR STOPPED");
      if (digitalRead(reset) == HIGH) {
        lcd.clear();
        lcd.print("RESETTING");
        delay(1000);
        break;
      }     
    }
  }
  }

