#include "TempSensor.h"
TempSensor::TempSensor(int p) : pin(p) { pinMode(pin, INPUT); }
float TempSensor::getTemperature() {
  int reading = analogRead(pin);
  float voltage = reading * 5.0 / 1024.0;
  return voltage * 100.0;
}
