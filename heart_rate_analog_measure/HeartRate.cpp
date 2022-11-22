#include "HeartRate.h"
#include "arduino.h"

HeartBeat::HeartBeat(unsigned long prev){
  this->timestamp = millis();
  this->interval = timestamp - prev;
}

HeartRate::HeartRate(short pin){
  this->pin = pin;
  this->heartBeats = new HeartBeats();
}

HeartRate::~HeartRate(){
  delete heartBeats;
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
    heartBeats->clear();
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

      heartBeats->push();
      isPeak = true;

      if(heartBeats->size <= HEARTBEATS_BUFFER_SIZE) state = ADJUSTING;
      else{
        state = MEASURING;
        heartBeats->pop();
        BPM = calculateHeartbeat();
        HRV = calculateHRV();
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

int HeartRate::calculateHeartbeat(){
  HeartBeat* current = heartBeats->head;

  unsigned long total = 0;

  while(current){
    total += current->interval;
    current = current->next;
  }

  return 60000 / (total / heartBeats->size);
}

int HeartRate::calculateHRV(){
  HeartBeat* current = heartBeats->head;

  unsigned long min = current->interval;
  unsigned long max = current->interval;

  while(current){
    if(current->interval < min) min = current->interval;
    if(current->interval > max) max = current->interval;

    current = current->next;
  }

  return max - min;
}