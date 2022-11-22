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

  if((measurements[0] >= 800 && measurements[1] < 800) || (measurements[0] <= 300 && measurements[1] > 300)) {
    clearHeartBeats();
    if(state == MEASURING || state == ADJUSTING){
      state = IDLE;
    }
    else if(state == IDLE){
      state = ADJUSTING;
    }
  }

  if(state == ADJUSTING || state == MEASURING){
    calculateThreshold();

    if(measurements[0] < thresholdLow) isPeak = false;

    if( measurements[0] >= thresholdHigh &&  measurements[1] < thresholdHigh && !isPeak){
      digitalWrite(13, HIGH);

      addHeartBeat();
      isPeak = true;

      if(heartBeatsAmount <= HEARTBEATS_BUFFER_SIZE) state = ADJUSTING;
      else{
        state = MEASURING;
        popHeartBeat();
        heartRate = calculateHeartbeat();
      }
    }
    else{
      digitalWrite(13,LOW);
    }
  }

  return value;
}

void HeartRate::calculateThreshold(){
  thresholdHigh = ampMax - ampMin;
  thresholdHigh *= 0.80;
  thresholdHigh += ampMin;

  thresholdLow = ampMax - ampMin;
  thresholdLow *= 0.50;
  thresholdLow += ampMin;
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
}

void HeartRate::clearHeartBeats(){
    HeartBeat* current = heartBeats;

    while(current){
       HeartBeat* temp = current->next;
       delete current;
       current = current->next;
    }

    heartBeats = nullptr;
    heartBeatsAmount = 0;
}

int HeartRate::calculateHeartbeat(){
  HeartBeat* current = heartBeats;

  unsigned long total = 0;

  while(current){
    total += current->interval;
    current = current->next;
  }

  return 60000 / (total / heartBeatsAmount);
}
