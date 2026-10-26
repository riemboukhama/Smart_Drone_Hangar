#include "Led.h"
Led::Led(int p) : pin(p), state(false) { pinMode(pin, OUTPUT); turnOff(); }
void Led::turnOn() { digitalWrite(pin, HIGH); state = true; }
void Led::turnOff() { digitalWrite(pin, LOW); state = false; }
void Led::toggle() { state = !state; digitalWrite(pin, state ? HIGH : LOW); }
