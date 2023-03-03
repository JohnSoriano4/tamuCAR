//THIS IS V1.1 OF THE CODE FOR THE TEXAS A&M 2023 CHEM-E CAR TEAM
//IMPORTANT TO NOTE:
//1. THE PHOTORESISTORS SENSITIVITY CAN BE ADJUSTED, IF YOU FIND THAT THEY TRIGGER TOO EARLY OR NOT AT ALL, PLEASE ADJUST THE SENSE VARIABLES
//2. THE ARDUINO WILL OUTPUT TO BOTH THE LCD DISPLAY AND ALSO THE SERIAL MONITOR. FIND THE SERIAL MONITOR WITH >TOOLS>SERIAL MONITOR
//3. THE SWITCH HAS TWO STATES: OFF IS DEFAULT, IN THIS STATE, THE VALVE WILL BE CLOSED AND THE MOTOR WILL NOT RUN AT ALL
//3.A WHEN THE SWITCH IS TURNED ON, THE TIMING VALVE WILL OPEN AND THE SENSORS WILL BE ACTIVE, THE MOTOR WILL BEGIN AND WILL RUN UNTIL AT LEAST 3 OF THE TRIGGER THRESHOLDS HAVE BEEN MET

#include <LiquidCrystal.h>
#include <Servo.h>

//initialize display and servo
Servo valve;

//Initialize analog pins for photoresistors
int motor = 13;
int stir = 11;
int status;
int switchpin = 12;

void setup() {
  Serial.begin(9600);
  pinMode(switchpin, INPUT);
  pinMode(motor, OUTPUT);
  valve.attach(10);
  Serial.println("initializing");
  delay(1000);
  
//START MOTOR
}

void loop() {
    status = digitalRead(switchpin);
    if (status == HIGH) {
      digitalWrite(stir, HIGH);
      digitalWrite(motor, HIGH);
      valve.write(180);
      delay(100);
    }

    if (status == LOW) {
      valve.write(0);
      digitalWrite(stir, LOW);
      digitalWrite(motor, LOW);
      Serial.println("not operating");
      delay(100);
    }
}