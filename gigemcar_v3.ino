#include <ESP32Servo.h>

//Initializes Servo "Object" controlling the valve
Servo valve;

//Pin IDs for the attatched hardware
const int photo1 = 39;
const int photo2 = 34;
const int photo3 = 35;
const int photo4 = 32;
const int startlever = 25;
const int servoPin = 33;
const int motor = 23;

//State variables for things
int off1 = 0;
int off2 = 0;
int off3 = 0;
int off4 = 0;
int offTotal = 0;
int status = 0;
int status2 = 0;

//Photoresistor Sensitivities????
const int sense1 = 200;
const int sense2 = 200;
const int sense3 = 200;
const int sense4 = 1200;

int timer = 0;

void setup() {
  Serial.begin(115200);
  valve.attach(servoPin, 1000, 2000);

  //Initialize hardware
  pinMode(photo1, INPUT);
  pinMode(photo2, INPUT);
  pinMode(photo3, INPUT);
  pinMode(photo4, INPUT);

  pinMode(startlever, INPUT); // Use internal pull-up resistor

  pinMode(motor, OUTPUT);
  delay(3000);
}

void loop() {
  status = digitalRead(startlever);
  Serial.println("Status: " + String(status)); // Print status for debugging
  if (status == HIGH) {
    Serial.println("starting");
    valve.write(180); //OPEN VALVE
    timer = timer + 100; //RUN TIMER    <- Ask about using arduino-timer https://github.com/contrem/arduino-timer
    digitalWrite(motor, HIGH);
    lightcheckFunction(); //CHECK PHOTORESISTORS
    delay(100); //10 CYCLES PER SECOND     <- Ask about making faster
  } 
  else {
    valve.write(0);
    digitalWrite(motor, LOW);
    Serial.println("not operating");
    delay(250);
  }
}

void lightcheckFunction() {
  int light1 = analogRead(photo1);
  int light2 = analogRead(photo2);
  int light3 = analogRead(photo3);
  int light4 = analogRead(photo4);

  off1 = (light1 < sense1) ? 1 : 0;
  off2 = (light2 < sense2) ? 1 : 0;
  off3 = (light3 < sense3) ? 1 : 0;
  off4 = (light4 < sense4) ? 1 : 0;

  offTotal = off1 + off2 + off3 + off4;

  Serial.println("RUNNING");
  Serial.print('\t');
  Serial.print(light1);
  Serial.print('\t');
  Serial.print(light2);
  Serial.print('\t');
  Serial.print(light3);
  Serial.print('\t');
  Serial.print(light4);
  Serial.print('\t');
  Serial.print(off1);
  Serial.print(off2);
  Serial.print(off3);
  Serial.print(off4);
  Serial.print("\t");
  Serial.println(offTotal);

  if (offTotal > 2) {
    Serial.println("STOPPED");
    digitalWrite(motor, LOW);
    Serial.println("final time");
    Serial.println(timer);

    while (true) {
      status2 = digitalRead(startlever);
      if (status2==LOW){
        Serial.println("reset");
        timer =0;
        break;
      }

  
    }
  }
}
