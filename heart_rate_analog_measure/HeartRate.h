#pragma once
#include "Arduino.h"
#include "HeartBeats.h"

#define MEASUREMENTS_BUFFER_SIZE 50
#define HEARTBEATS_BUFFER_SIZE 10

enum{
  IDLE,
  ADJUSTING,
  MEASURING
};

class HeartRate{
public:
  int BPM;
  int HRV;
  HeartBeats* heartBeats;
  int state = IDLE;
  HeartRate(short pin);
  ~HeartRate();
  int measure();

private:
  int measurements[MEASUREMENTS_BUFFER_SIZE];
  float thresholdHigh = 0;
  float thresholdLow = 0;
  int ampMin = 0;
  int ampMax = 0;
  short pin;
  bool isPeak = false;
  void calculateThreshold();
  int calculateHeartbeat(); 
  int calculateHRV();
};