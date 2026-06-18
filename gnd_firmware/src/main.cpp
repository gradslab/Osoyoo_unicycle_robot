#include <Arduino.h>
#include <SoftwareSerial.h>

// BT: J13 jumpers set to D11/D4
SoftwareSerial btSerial(11, 4); // RX=D11, TX=D4

void handleCommand(char cmd);
void stopMotors();

// Motor pins (fixed by shield)
#define IN1 12  // Left motor direction
#define IN2 11  // Left motor direction
#define IN3 9   // Right motor direction
#define IN4 10  // Right motor direction
#define ENA 5   // Left motor speed (PWM)
#define ENB 6   // Right motor speed (PWM)

int motorSpeed = 150; // 0-255

void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);

  // Ensure motors are off at startup
  stopMotors();

  Serial.begin(9600);
  btSerial.begin(9600);
  Serial.println("Ready. Send F/B/L/R/S");
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();
    Serial.print("CMD: "); Serial.println(cmd);
    handleCommand(cmd);
  }
}

void handleCommand(char cmd) {
  switch (cmd) {
    case 'F': case 'f': Serial.println("F"); break;
    case 'B': case 'b': Serial.println("B"); break;
    case 'L': case 'l': Serial.println("L"); break;
    case 'R': case 'r': Serial.println("R"); break;
    case 'S': case 's': stopMotors(); break;
  }
}

void stopMotors(){ digitalWrite(IN1,LOW); digitalWrite(IN2,LOW);
                   digitalWrite(IN3,LOW); digitalWrite(IN4,LOW);
                   analogWrite(ENA, 0);   analogWrite(ENB, 0); }