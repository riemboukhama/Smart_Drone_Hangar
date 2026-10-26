#include "Sonar.h"
Sonar::Sonar(int trig, int echo) : trigPin(trig), echoPin(echo) {
  pinMode(trigPin, OUTPUT); pinMode(echoPin, INPUT);
}
long Sonar::getDistance() {
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10); digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 30000);
  return duration == 0 ? 999 : duration * 0.034 / 2;
}
