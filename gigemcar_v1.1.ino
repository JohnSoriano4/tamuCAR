//THIS IS V1.1 OF THE CODE FOR THE TEXAS A&M 2023 CHEM-E CAR TEAM
//IMPORTANT TO NOTE:
//1. THE PHOTORESISTORS SENSITIVITY CAN BE ADJUSTED, IF YOU FIND THAT THEY TRIGGER TOO EARLY OR NOT AT ALL, PLEASE ADJUST THE SENSE VARIABLES
//2. THE ARDUINO WILL OUTPUT TO BOTH THE LCD DISPLAY AND ALSO THE SERIAL MONITOR. FIND THE SERIAL MONITOR WITH >TOOLS>SERIAL MONITOR
//3. THE SWITCH HAS TWO STATES: OFF IS DEFAULT, IN THIS STATE, THE VALVE WILL BE CLOSED AND THE MOTOR WILL NOT RUN AT ALL
//3.A WHEN THE SWITCH IS TURNED ON, THE TIMING VALVE WILL OPEN AND THE SENSORS WILL BE ACTIVE, THE MOTOR WILL BEGIN AND WILL RUN UNTIL AT LEAST 3 OF THE TRIGGER THRESHOLDS HAVE BEEN MET

#include <LiquidCrystal.h>
#include <Servo.h>

//initialize display and servo
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo valve;

//Initialize analog pins for photoresistors
int photo1 = A2; 
int photo2 = A3;
int photo3 = A4;
int photo4 = A5;
int motor = 3;
int status;
int switchpin = 12;

//photoresistor variables
int off1;
int off2;
int off3;
int off4;
int offTotal;
//ADJUST THIS VARIABLE TO ADJUST THE THRESHOLD FOR THE LIGHT SENSING. HIGHER VALUES MEANS PROGRAM WILL ACTIVATE AT HIGHER LIGHT VALUES. THE THRESHOLD IS PRIMARILY DEPENDENT ON YOUR PULL DOWN RESISTOR!
int sense1 = 100;
int sense2 = 600;
int sense3 = 400;
int sense4 = 400;

int timer = 0;

void setup() {
  Serial.begin(9600);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(switchpin, INPUT);
  pinMode(motor, OUTPUT);
  valve.attach(10);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("initializing");
  Serial.println("initializing");
  delay(3000);
  lcd.print("STARTING");
  delay(1000);
  
//START MOTOR
  digitalWrite(motor, HIGH);
}

void loop() {
    status = digitalRead(switchpin);
    if (status == HIGH) {
      valve.write(180);
      lightcheckFunction();
      timer = timer + 100;
      delay(100);
    }

    if (status == LOW) {
      valve.write(0);
      Serial.println("not operating");
      delay(500);
    }
}

int lightcheckFunction(){
  //This checks each individual photoresistor
  int light1 = analogRead(photo1);
  int light2 = analogRead(photo2);
  int light3 = analogRead(photo3);
  int light4 = analogRead(photo4);

  //Printing to LCD display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(light1);
  lcd.setCursor(5, 0);
  lcd.print(light2);
  lcd.setCursor(10, 0);
  lcd.print(light3);
  lcd.setCursor(0, 1);
  lcd.print("TIMER");
  lcd.setCursor(1,7);
  lcd.print(timer);

  //Printing to Serial monitor
  Serial.print(light1);
  Serial.print('\t');
  Serial.print(light2);
  Serial.print('\t');
  Serial.print(light3);
  Serial.print('\n');
  Serial.print("OPERATING");

  //Checking photoresistor
  if (light1 < sense1) {
    off1 = 1;
  } else {
    off1 = 0;
  }

  if (light2 < sense2) {
    off2 = 1;
  } else {
    off2 = 0;
  }

  if (light3 < sense3) {
    off3 = 1;
  } else {
    off3 = 0;
  }

  if (light4 < sense4) {
    off4 = 1;
  } else {
    off4 = 0;
  }

  offTotal = off1 + off2 + off3 + off4;
  
  if (offTotal > 2) {
    Serial.println("STOPPED");
    digitalWrite(motor, LOW);
    Serial.println("final time");
    Serial.println(timer);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("STOP");
    lcd.setCursor(1,5);
    lcd.print(timer);
    
    while (true) {
      Serial.println("STOPPED");
      Serial.println(timer);
      lcd.setCursor(1,0);
      lcd.print("STOP");
      delay(3000);
      } 
    }         

}
