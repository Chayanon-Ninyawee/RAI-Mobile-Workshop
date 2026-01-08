#include <Arduino.h>

/*
===============================================================================
 EXERISE 3: BASIC MOTOR CONTROL
-------------------------------------------------------------------------------
 1) Make the robot move forward for 2 seconds.
 2) Stop for 2 seconds then loop.
 3) Change SPEED and observe behavior.

 Questions:
   - Why does PWM control speed?
   - What happens if SPEED > 255?
===============================================================================
*/

constexpr byte MOTOR_LEFT_1 = 5;
constexpr byte MOTOR_LEFT_2 = 4;
constexpr byte MOTOR_LEFT_EN = 3;

constexpr byte MOTOR_RIGHT_1 = 8;
constexpr byte MOTOR_RIGHT_2 = 7;
constexpr byte MOTOR_RIGHT_EN = 6;

// --- Motor Controller --
void motorBegin();
void setMotorSpeed(byte in1, byte in2, byte en, int speed);
void motorMove(int leftSpeed, int rightSpeed);

void motorBegin() {
    pinMode(MOTOR_LEFT_1, OUTPUT);
    pinMode(MOTOR_LEFT_2, OUTPUT);
    pinMode(MOTOR_LEFT_EN, OUTPUT);

    pinMode(MOTOR_RIGHT_1, OUTPUT);
    pinMode(MOTOR_RIGHT_2, OUTPUT);
    pinMode(MOTOR_RIGHT_EN, OUTPUT);

    motorMove(0, 0);
}

void setMotorSpeed(byte in1, byte in2, byte en, int speed) {
    // Clamp speed
    if (speed > 255) speed = 255;
    if (speed < -255) speed = -255;

    if (speed > 0) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
    } else if (speed < 0) {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
    } else {
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
    }

    analogWrite(en, abs(speed));
}

void motorMove(int leftSpeed, int rightSpeed) {
    setMotorSpeed(MOTOR_LEFT_1, MOTOR_LEFT_2, MOTOR_LEFT_EN, leftSpeed);
    setMotorSpeed(MOTOR_RIGHT_1, MOTOR_RIGHT_2, MOTOR_RIGHT_EN, rightSpeed);
}

void setup() {
    motorBegin();
}

// NOTE: Start your exercise here

// Change this to see different behevior.
// Even change it to negative.
int SPEED = 150;

// Why does it only move forward?
// I think you know how to fix it.
void loop() {
    motorMove(SPEED, SPEED);
    delay(2000);
}
