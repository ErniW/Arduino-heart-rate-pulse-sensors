#include "HeartRate.h"

HeartRate* heartRate = new HeartRate(A0);

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop(){
  int value = heartRate->measure();
  delay(20);

  switch(heartRate->state){
    case IDLE:
      Serial.println("IDLE");
      break;
    case ADJUSTING:
      Serial.print("ADJUSTING, Pulses detected: ");
      Serial.println(heartRate->heartBeats->size);
      break;
    case MEASURING:
      Serial.print("MEASURING ");
      //Serial.print(heartRate->HRV);
      //Serial.print(", ");
      Serial.println(heartRate->BPM);
  }

}
