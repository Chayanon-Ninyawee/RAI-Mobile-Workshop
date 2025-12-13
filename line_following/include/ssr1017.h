#pragma once
#include <Arduino.h>

class SSR1017
{
private:
    uint8_t pin;

public:
    SSR1017(uint8_t digitalPin);
    void begin();
    bool read();  // returns true/1 = black line detected
};
