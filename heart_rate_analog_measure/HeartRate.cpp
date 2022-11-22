#include "HeartRate.h"
#include "arduino.h"

HeartBeat::HeartBeat(unsigned long prev){
  this->timestamp = millis();
  this->interval = timestamp - prev;
}

HeartRate::HeartRate(short pin){
  this->pin = pin;
}

int HeartRate::measure(){
  int value = analogRead(pin);

  ampMin = value;
  ampMax = value;

  for(int i = MEASUREMENTS_BUFFER_SIZE - 1;  i >= 0; i--){
    measurements[i+1] = measurements[i];

    if(measurements[i+1] < ampMin) ampMin = measurements[i+1];
    if(measurements[i+1] > ampMax) ampMax = measurements[i+1];

  }

  measurements[0] = value;

  calculateThreshold();

    // Serial.print("New measure: ");
    // Serial.print(value);
    // Serial.print(", Threshold: ");
    // Serial.print(threshold);
    // Serial.print(", ");
    // Serial.print(", Previous value: ");
    // Serial.print(measurements[1]);

  if( measurements[0] >= threshold &&  measurements[1] < threshold){
    //Serial.print(", HEARTBEAT");
    digitalWrite(13, HIGH);
    // Serial.print(threshold);
    // Serial.print(", ");
    // Serial.print(value);
    // Serial.print(", ");
    // Serial.println(measurements[1]);


    addHeartBeat();

    if(heartBeatsAmount <= HEARTBEATS_BUFFER_SIZE) state = ADJUSTING;
    else{
      state = MEASURING;
      popHeartBeat();
      calculateHeartbeat();
    }
  }
  else{
    digitalWrite(13,LOW);
    
  }
  //Serial.println();

  return value;
}

void HeartRate::calculateThreshold(){
  threshold = ampMax - ampMin;
  threshold *= 0.80;
  threshold += ampMin;
}

void HeartRate::addHeartBeat(){
  heartBeatsAmount++;

  if(!heartBeats){
    heartBeats = new HeartBeat(0);
    heartBeatsTail = heartBeats;
    return;
  }

  HeartBeat* temp = new HeartBeat(heartBeats->timestamp);
  temp->next = heartBeats;
  heartBeats->prev = temp;
  heartBeats = temp;
}

void HeartRate::popHeartBeat(){
  heartBeatsAmount--;

  HeartBeat* toRemove = heartBeatsTail;
  HeartBeat* temp = heartBeatsTail->prev;

  delete toRemove;
  heartBeatsTail = temp;
  heartBeatsTail->next = nullptr;
  
  // if(heartBeatsTail->prev) heartBeatsTail = heartBeatsTail->prev;

  // delete toRemove;
}

void HeartRate::calculateHeartbeat(){
  HeartBeat* current = heartBeats;

  unsigned long total = 0;

  while(current){
    total += current->interval;
    current = current->next;
  }

  heartRate = total / heartBeatsAmount;
  Serial.print(heartRate);
  Serial.print('\t');
  heartRate = 60000 / heartRate;
   Serial.println(heartRate);

}
