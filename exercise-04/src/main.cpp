#include <Arduino.h>

#include "Servo.h"

/*
===============================================================================
 EXERISE 4: SERVO CONTROL
-------------------------------------------------------------------------------
 1) Attach servo.
 2) Find correct open/close angles.
 3) Avoid buzzing.
 4) Use the value in the line_following program.

 Questions:
   - Why does servo use angles instead of speed?
===============================================================================
*/

constexpr byte SERVO_PIN = A0;
constexpr int SERVO_CLOSE = 0;   // FIXME: Change this value
constexpr int SERVO_OPEN = 180;  // FIXME: Change this value

Servo servo;

void setup() {
    servo.attach(SERVO_PIN);
}

void loop() {
    servo.write(SERVO_CLOSE);
    delay(2000);

    servo.write(SERVO_OPEN);
    delay(2000);
}
