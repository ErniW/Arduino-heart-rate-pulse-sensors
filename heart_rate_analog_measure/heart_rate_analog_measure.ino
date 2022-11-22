#include "HeartRate.h"

HeartRate* heartRate = new HeartRate(A0);

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop(){
  int value = heartRate->measure();
  delay(20);
}
