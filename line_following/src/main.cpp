#include <Arduino.h>

#include "Servo.h"

// --- Motors ---
constexpr byte MOTOR_LEFT_1 = 7;
constexpr byte MOTOR_LEFT_2 = 8;
constexpr byte MOTOR_LEFT_EN = 6;

constexpr byte MOTOR_RIGHT_1 = 4;
constexpr byte MOTOR_RIGHT_2 = 10;
constexpr byte MOTOR_RIGHT_EN = 5;

// --- Servo ---
constexpr byte SERVO_PIN = A0;
constexpr int SERVO_CLOSE = 0;   // FIXME: Change this value
constexpr int SERVO_OPEN = 180;  // FIXME: Change this value

Servo servo;

// --- IR Servo ---
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

// --- PID Controller ---
float pidIntegral = 0.0;
float pidLastError = 0.0;
unsigned long pidLastTime = 0;

/*
 * @param error Current measured value from the sensor.
 * @param kP    Proportional gain constant.
 * @param kI    Integral gain constant.
 * @param kD    Derivative gain constant.
 *
 * @return PID control output as an integer
 */
int pidCompute(float error, float kP, float kI, float kD) {
    unsigned long now = millis();
    float dt = (now - pidLastTime) / 1000.0;

    // First run protection
    if (pidLastTime == 0) {
        pidLastTime = now;
        pidLastError = error;
        return 0;
    }

    // Integral
    pidIntegral += error * dt;

    // Derivative
    float derivative = (error - pidLastError) / dt;

    // PID output
    float output = (kP * error) + (kI * pidIntegral) + (kD * derivative);

    pidLastError = error;
    pidLastTime = now;

    return (int)output;
}

void pidReset() {
    pidIntegral = 0.0;
    pidLastError = 0.0;
    pidLastTime = 0;
}

void setup() {
    Serial.begin(115200);

    motorBegin();

    servo.attach(SERVO_PIN);
    servo.write(SERVO_CLOSE);

    pinMode(IR_LEFT, INPUT);
    pinMode(IR_MID, INPUT);
    pinMode(IR_RIGHT, INPUT);
}

// --- Speed of the robot ---
int forwardSpeed = 100;
int turnSpeed = 100;

// --- Value that will trigger the IR as being on the line ---
int irLeftTrigger = 550;
int irMidTrigger = 550;
int irRightTrigger = 400;

// NOTE: This is the pid controller in case you are bored and
// want to try medium or hard track, which may require PID controller
float KP = 0.2f;
float KI = 0.0f;
float KD = 0.004f;
int irMidTarget = 500;

void loop() {
    // NOTE: The value are from 0 - 1023
    int irLeft = analogRead(IR_LEFT);
    int irMid = analogRead(IR_MID);
    int irRight = analogRead(IR_RIGHT);

    // TODO: Write your control code here

    // NOTE: Uncomment this if you want to use PID
    // WARN: Ask TA first before you can use PID
    // float irMidError = irMid - irMidTarget;
    // int correction = pidCompute(irMidError, KP, KI, KD);
    // int leftSpeed = forwardSpeed - correction;
    // int rightSpeed = forwardSpeed + correction;
    // motorMove(leftSpeed, rightSpeed);

    // Debug
    Serial.print(irLeft);
    Serial.print(" ");
    Serial.print(irMid);
    Serial.print(" ");
    Serial.println(irRight);
}
