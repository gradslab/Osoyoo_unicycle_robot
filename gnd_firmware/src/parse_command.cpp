// parse_command.cpp
#include <Arduino.h>
#include <math.h>

#include "config.h"
#include "parse_command.h"

MotorCommand parseCommand(String input) {
    // MotorCommand is a struct with members leftSpeed and rightSpeed corresponding the commanded left and right motor speeds
    MotorCommand cmd = {0, 0};
    
    // command input has format: "L(-?)XXX,R(-?)XXX"; negative values indicates backwards rotation
    // find comma; if not found, then cmd is invalid (stops the bot by sending cmd={0,0})
    int commaIndex = input.indexOf(',');
    if (commaIndex == -1) {
        Serial.println("error: no comma detected (wrong command format?)");
        return cmd;
    }
    // parse left and right speeds
    cmd.leftSpeed  = input.substring(1, commaIndex).toInt();
    cmd.rightSpeed = input.substring(input.indexOf('R') + 1).toInt();

    // enforce maximum (255) and minimum values (-255)
    cmd.leftSpeed  = constrain(cmd.leftSpeed,  -255, 255);
    cmd.rightSpeed = constrain(cmd.rightSpeed, -255, 255);
    
    return cmd;
}


void writeMotor(MotorCommand input) {
  // parse sign
  int leftSign = (input.leftSpeed > 0) - (input.leftSpeed < 0);
  int rightSign = (input.rightSpeed > 0) - (input.rightSpeed < 0);

  // set motor directions via IN1, IN2, IN3, IN4
  switch(leftSign) {
    case -1:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      break;
    case 1:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      break;
    default:
      // value of '0' will make the motor coast 
      // ----> !!! change this to HIGH, HIGH if you want the motor to aggressively stop !!! <---
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      break;
  }

  switch(rightSign) {
    case -1:
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;
    case 1:
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;
    default:
      // value of '0' will stop the motors 
      // -----> !!! change this too !!! <-------
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
  }

  // write magnitude of speed to motor
  analogWrite(ENA, abs(input.leftSpeed));
  analogWrite(ENB, abs(input.rightSpeed));
}