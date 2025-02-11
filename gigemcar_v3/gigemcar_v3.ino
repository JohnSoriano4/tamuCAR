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

//both motors are on one circuit
const int motors = 23;

//State variables for things
bool photo1_isOff = 0;
bool photo2_isOff = 0;
bool photo3_isOff = 0;
bool photo4_isOff = 0;

uint8_t offTotal = 0;
int status = 0;
int status2 = 0;

int clockSpeed = 100; //In milliseconds

//Photoresistor Sensitivities
const int photo1_sense = 200;
const int photo2_sense = 200;
const int photo3_sense = 200;
const int photo4_sense = 1200;

int timer = 0;

void setup() {
  Serial.begin(115200); // Says what channel to display serial data to
  valve.write(0); // Ensures that the servo is closed upon starting
  valve.attach(servoPin, 1000, 2000); //Possibly tweak these values

  //Initialize hardware
  pinMode(photo1, INPUT);
  pinMode(photo2, INPUT);
  pinMode(photo3, INPUT);
  pinMode(photo4, INPUT);

  pinMode(startlever, INPUT); // Use internal pull-up resistor

  pinMode(motors, OUTPUT);
  delay(3000);
}

void loop() {
  status = digitalRead(startlever);
  Serial.println("Status: " + String(status)); // Print status for debugging
  if (status == HIGH) {
    Serial.println("starting");
    valve.write(180); //OPEN VALVE
    timer = timer + 100; //RUN TIMER
    digitalWrite(motors, HIGH);
    lightcheckFunction(); //CHECK PHOTORESISTORS
    delay(clockSpeed); 
  } 
  else {
    valve.write(0);
    digitalWrite(motors, LOW);
    Serial.println("not operating");
    delay(250);
  }
}

void lightcheckFunction() {
  int photo1_val = analogRead(photo1);
  int photo2_val = analogRead(photo2);
  int photo3_val = analogRead(photo3);
  int photo4_val = analogRead(photo4);

  //If the light value is higher than the sensitivity, 
  //then the value will stay false, otherwise it will flip
  photo1_isOff = (photo1_val < photo1_sense);
  photo2_isOff = (photo2_val < photo2_sense);
  photo3_isOff = (photo3_val < photo3_sense);
  photo4_isOff = (photo4_val < photo4_sense);
 
  offTotal = photo1_isOff + photo2_isOff + photo3_isOff + photo4_isOff;

  Serial.println("RUNNING");
  Serial.print('\t');
  Serial.print(photo1_val);
  Serial.print('\t');
  Serial.print(photo2_val);
  Serial.print('\t');
  Serial.print(photo3_val);
  Serial.print('\t');
  Serial.print(photo4_val);
  Serial.print('\t');
  Serial.print(photo1_isOff);
  Serial.print(photo2_isOff);
  Serial.print(photo3_isOff);
  Serial.print(photo4_isOff);
  Serial.print("\t");
  Serial.println(offTotal);

  //Checks if any three are on using boolean logic
  //if ((photo1_isOff && photo2_isOff && photo3_isOff) || (photo1_isOff && photo2_isOff && photo4_isOff) || (photo2_isOff && photo3_isOff && photo4_isOff) || (photo1_isOff && photo3_isOff && photo4_isOff)) {
  if (offTotal >= 3) 
  {
    Serial.println("STOPPED");
    digitalWrite(motors, LOW);
    Serial.println("final time");
    Serial.println(timer);

    while (true) 
    { //why is this only here
      status2 = digitalRead(startlever);
      if (status2==LOW)
      {
        Serial.println("reset");
        timer = 0;
        break;
      }

  
    }
  }
}
