#include <Arduino.h>

#include "Servo.h"

// --- Motors ---
constexpr byte MOTOR_LEFT_1 = 5;
constexpr byte MOTOR_LEFT_2 = 4;
constexpr byte MOTOR_LEFT_EN = 3;

constexpr byte MOTOR_RIGHT_1 = 8;
constexpr byte MOTOR_RIGHT_2 = 7;
constexpr byte MOTOR_RIGHT_EN = 6;

// --- Servo ---
constexpr byte SERVO_PIN = 2;
constexpr int SERVO_CLOSE = 0;   // FIXME: Change this value
constexpr int SERVO_OPEN = 180;  // FIXME: Change this value

Servo servo;

// --- IR Sensor ---
constexpr byte IR_LEFT = A1;
constexpr byte IR_MID = A2;
constexpr byte IR_RIGHT = A3;

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
    Serial.begin(115200);

    motorBegin();

    servo.attach(SERVO_PIN);
    servo.write(SERVO_CLOSE);

    pinMode(IR_LEFT, INPUT);
    pinMode(IR_MID, INPUT);
    pinMode(IR_RIGHT, INPUT);

    delay(1000);
}

// --- Speed of the robot ---
int forwardSpeed = 100;
int turnSpeed = 100;

// --- Value that will trigger the IR as being on the line ---
int irLeftTrigger = 500;   // FIXME: Change this value
int irMidTrigger = 500;    // FIXME: Change this value
int irRightTrigger = 500;  // FIXME: Change this value

void loop() {
    // Move forward
    motorMove(forwardSpeed, forwardSpeed);
    delay(500);

    // Move backward
    motorMove(-forwardSpeed, -forwardSpeed);
    delay(500);

    // Turn right
    motorMove(turnSpeed, -turnSpeed);
    delay(500);

    // Turn left
    motorMove(-turnSpeed, turnSpeed);
    delay(1000);
}
