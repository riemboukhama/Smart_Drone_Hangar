#include "Button.h"

Button::Button(int p) : pin(p), lastState(HIGH) {
    pinMode(pin, INPUT_PULLUP);
}

bool Button::isPressed() {
    bool currentState = digitalRead(pin);
    bool pressed = (lastState == HIGH && currentState == LOW);
    lastState = currentState;
    return pressed;
}

int Button::getPin() {
    return pin;
}