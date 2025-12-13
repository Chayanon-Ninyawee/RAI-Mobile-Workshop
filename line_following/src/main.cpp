#include <Arduino.h>

#include "Servo.h"
#include "motor_controller.h"
#include "ssr1017.h"

// --- Motors ---
constexpr byte MOTOR_LEFT_1 = 7;
constexpr byte MOTOR_LEFT_2 = 8;
constexpr byte MOTOR_LEFT_EN = 6;

constexpr byte MOTOR_RIGHT_1 = 4;
constexpr byte MOTOR_RIGHT_2 = 10;
constexpr byte MOTOR_RIGHT_EN = 5;

MotorController robotMotors(MOTOR_LEFT_1, MOTOR_LEFT_2, MOTOR_LEFT_EN, MOTOR_RIGHT_1, MOTOR_RIGHT_2, MOTOR_RIGHT_EN);

// --- Servo ---
constexpr byte SERVO_PIN = A0;
constexpr int SERVO_CLOSE = 0;   // FIXME: Change this value
constexpr int SERVO_OPEN = 180;  // FIXME: Change this value

Servo servo;

// --- IR Servo ---
SSR1017 irLeft(2);
SSR1017 irMid(3);
SSR1017 irRight(11);

// --- Base Speeds ---
int forwardSpeed = 150;
int turnSpeed = 130;

void setup() {
    Serial.begin(115200);

    robotMotors.begin();

    servo.attach(SERVO_PIN);
    servo.write(SERVO_CLOSE);

    irLeft.begin();
    irMid.begin();
    irRight.begin();
}

void loop() {
    bool L = irLeft.read();
    bool C = irMid.read();
    bool R = irRight.read();

    // TODO: Write your control code here

    // Debug
    Serial.print(L);
    Serial.print(" ");
    Serial.print(C);
    Serial.print(" ");
    Serial.println(R);
}
