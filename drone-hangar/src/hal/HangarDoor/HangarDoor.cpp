#include "HangarDoor.h"
HangarDoor::HangarDoor(int p) : pin(p) {}
void HangarDoor::init() { servo.attach(pin); close(); }
void HangarDoor::open() { servo.write(90); }
void HangarDoor::close() { servo.write(0); }
