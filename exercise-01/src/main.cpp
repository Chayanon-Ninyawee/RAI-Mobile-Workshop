#include <Arduino.h>

/*
===============================================================================
 EXERISE 1: ARDUINO PROGRAM STRUCTURE
-------------------------------------------------------------------------------
 1) Upload this code.
 2) Open Serial Monitor at 115200 baud.

 Questions:
   - Why does "Hello from setup" print once?
   - Why does "Hello from loop" print forever?
   - How ofter does "Hello from loop" print (in seconds)?
===============================================================================
*/

void setup() {
    Serial.begin(115200);
    Serial.println("Hello from setup");

    delay(1000);
}

void loop() {
    Serial.println("Hello from loop");
    delay(500);
}
