#include <Servo.h>

Servo servomotor;

int switchpin = 1;
int position = 0;
int status;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servomotor.attach(2);
}

void loop() {
  status = digitalRead(switchpin);
  if (status == HIGH) {
    Serial.println("switch on");
    servomotor.write(180);
    delay(3000);
  }

  if (status == LOW) {
    Serial.println("switch off");
    servomotor.write(0);
    delay(3000);
  }
}
