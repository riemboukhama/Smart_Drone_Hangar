#include "Pir.h"
Pir::Pir(int p) : pin(p) { pinMode(pin, INPUT); }
bool Pir::isDetected() { return digitalRead(pin) == HIGH; }
