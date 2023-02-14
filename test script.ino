//WELCOME TO THE TESTING SCRIPT, WE HOPE YOU FIND THIS USEFUL, IF THERE IS ANY QUESTIONS, JUST ASK IN THE SLACK
//IMPORTANT TO NOTE:
//1. THE PHOTORESISTORS SENSITIVITY CAN BE ADJUSTED, IF YOU FIND THAT THEY TRIGGER TOO EARLY OR NOT AT ALL, PLEASE ADJUST THE VARIABLE "SENSITIVITY" (<700 works pretty well)
//2. THE ARDUINO WILL OUTPUT TO BOTH THE LCD DISPLAY AND ALSO THE SERIAL MONITOR. FIND THE SERIAL MONITOR WITH >TOOLS>SERIAL MONITOR
//3. TO RESET, FLIP THE SWITCH TO OFF
//4. TO START, FLIP THE SWITCH TO ON (TIMER WILL BEGIN IMMEDIATELY UPON SWITCH FLIP)
//5. WHEN STARTING, THE ARDUINO HAS A FEW SECONDS DELAY, THEN THE DISPLAY/SERIAL MONITOR WILL READ "INITIALIZING" FOR 3 SECONDS BEFORE TIMER BEGINS, START THE REACTION DURING THIS TIME

#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Initialize analog pins for photoresistors
int photo1 = A1;
int photo2 = A2;
int photo3 = A3;

//inputs
int onswitch = 0;
int on = 0;

//variables
int off1;
int off2;
int off3;
int offTotal;
//ADJUST THIS VARIABLE TO ADJUST THE THRESHOLD FOR THE LIGHT SENSING. HIGHER VALUES MEANS PROGRAM WILL ACTIVATE AT HIGHER LIGHT VALUES.
int sensitivity = 600;
int timer = 0;

void setup() {
  Serial.begin(9600);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("initializing");
  Serial.println("initializing");
  delay(3000);
  lcd.print("STARTING");
  delay(1000);
}

void loop() {
  on = digitalRead(onswitch);
  while (on == HIGH) {
    lightcheckFunction();
    timer = timer + 250;
    delay(250);
    Serial.println(timer);
  }

  if (on == LOW){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("switch off");
    lcd.setCursor(1,0);
    lcd.print(timer);
    Serial.println("stopped");
    Serial.println(timer);
    timer = 0;
    while (true){
      on = digitalRead(onswitch);
      if (on == HIGH) {
        break;
      }
    }          
  }
  
}

int lightcheckFunction(){
  //This checks each individual photoresistor
  int light1 = analogRead(photo1);
  int light2 = analogRead(photo2);
  int light3 = analogRead(photo3);

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
  Serial.print("OPERATING");
  Serial.print('\t');
  Serial.print(light1);
  Serial.print('\t');
  Serial.print(light2);
  Serial.print('\t');
  Serial.print(light3);
  Serial.print('\n');


  //Checking photoresistor
  if (light1 < sensitivity) {
    off1 = 1;
  } else {
    off1 = 0;
  }

  if (light2 < sensitivity) {
    off2 = 1;
  } else {
    off2 = 0;
  }

  if (light3 < sensitivity) {
    off3 = 1;
  } else {
    off3 = 0;
  }
  offTotal = off1 + off2 + off3;
  
  if (offTotal > 1) {
    Serial.println("STOPPED");
    Serial.println("final time");
    Serial.println(timer);
    lcd.setCursor(1,0);
    lcd.print("STOP");
    lcd.setCursor(1,5);
    lcd.print(timer);
    
    while (true) {
      on = digitalRead(onswitch);
      if (on == LOW) {
        break;
      } 
    }         
  }
}
