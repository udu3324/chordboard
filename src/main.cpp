#include <Arduino.h>

const int ledTest = 21;

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  pinMode(ledTest, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("working!!!");
  digitalWrite(ledTest, HIGH);
  delay(500);
  digitalWrite(ledTest, LOW);
  delay(500);
}