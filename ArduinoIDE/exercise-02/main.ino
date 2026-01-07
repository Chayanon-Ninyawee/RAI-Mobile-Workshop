#include <Arduino.h>

/*
===============================================================================
 EXERISE 2.1: ANALOG READ (IR SENSORS)
-------------------------------------------------------------------------------
 1) Connect all IR sensor as shown in the diagram (A1 = LEFT, A2 = MID, A3 = RIGHT).
 2) Upload and open Serial Monitor at 115200 baud.
 3) Move the sensor over:
    - line
    - floor
    - air

 Questions:
   - What is the range of analogRead()? (Use the internet to find the answer)
   - How and why does light change the reading?
===============================================================================
*/

constexpr byte IR_LEFT = A1;
constexpr byte IR_MID = A2;
constexpr byte IR_RIGHT = A3;

void setup() {
    Serial.begin(115200);
    pinMode(IR_LEFT, INPUT);
    pinMode(IR_MID, INPUT);
    pinMode(IR_RIGHT, INPUT);
}

// NOTE: For Exercise 2.2
int irLeftTrigger = 550;
int irMidTrigger = 550;
int irRightTrigger = 550;

void loop() {
    Serial.println("==== Exercise 2.1 ====");

    int irLeft = analogRead(IR_LEFT);
    int irMid = analogRead(IR_MID);
    int irRight = analogRead(IR_RIGHT);

    Serial.print(irLeft);
    Serial.print(" ");
    Serial.print(irMid);
    Serial.print(" ");
    Serial.println(irRight);

    /*
    ===============================================================================
     EXERISE 2.2: ANALOG -> DIGITAL DECISION
    -------------------------------------------------------------------------------
     1) Adjust irTrigger so detection is reliable.
     2) Observe how printed state changes.
     3) Use the value in the line_following program.

     Questions:
       - Why do we need a threshold?
       - What happens if threshold is too high or low?
    ===============================================================================
    */

    Serial.println("");
    Serial.println("==== Exercise 2.2 ====");

    // NOTE: You need to flip 1-2 sign(s) so that it prints correctly
    bool irLeftOnLine = irLeft > irLeftTrigger;
    bool irMidOnLine = irMid < irMidTrigger;
    bool irRightOnLine = irRight < irRightTrigger;

    Serial.print(irLeftOnLine ? "LINE" : "FLOOR");
    Serial.print(" ");
    Serial.print(irMidOnLine ? "LINE" : "FLOOR");
    Serial.print(" ");
    Serial.println(irRightOnLine ? "LINE" : "FLOOR");

    Serial.println("");
    delay(100);
}
