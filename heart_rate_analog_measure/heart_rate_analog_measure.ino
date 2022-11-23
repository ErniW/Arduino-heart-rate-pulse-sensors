#include "HeartRate.h"

HeartRate* heartRate = new HeartRate(A0);

#define MEASUREMENT_INTERVAL 20

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

unsigned long prevTime = 0;

void loop(){
  unsigned long time = millis();
  if(time - prevTime > MEASUREMENT_INTERVAL){
    int value = heartRate->measure();
    prevTime = time;
  }

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
