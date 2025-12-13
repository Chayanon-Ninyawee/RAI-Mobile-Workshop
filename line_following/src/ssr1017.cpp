#include "ssr1017.h"

SSR1017::SSR1017(uint8_t digitalPin)
    : pin(digitalPin) {}

void SSR1017::begin() {
    pinMode(pin, INPUT);
}

bool SSR1017::read() {
    return digitalRead(pin);
}
