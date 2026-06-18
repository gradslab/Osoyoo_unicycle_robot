#include <Arduino.h>

#include "parse_command.h"
#include "config.h"

void stopMotors();

void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);

  stopMotors();

  Serial.begin(9600);
  Serial.println("serial port initialized");
}

void loop() {
  if (Serial.available()) {
    // USING \n AS A TERMINATOR
    String cmd = Serial.readStringUntil('\n');
    Serial.print("CMD: "); Serial.println(cmd);

    // command input has format: "L(-?)XXX,R(-?)XXX"; negative value indicates backwards rotation
    writeMotor(parseCommand(cmd));
  }
}

void stopMotors(){ 
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}