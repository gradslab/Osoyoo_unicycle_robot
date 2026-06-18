// parse_command.h
#include <Arduino.h>
#pragma once

struct MotorCommand {
    int leftSpeed;   // -255 to 255, negative = reverse
    int rightSpeed;
};

void writeMotor(MotorCommand input);
MotorCommand parseCommand(String input);