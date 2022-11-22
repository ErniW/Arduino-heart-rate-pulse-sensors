#pragma once
#include "Arduino.h"

#define MEASUREMENTS_BUFFER_SIZE 50
#define HEARTBEATS_BUFFER_SIZE 10

struct HeartBeat {
  unsigned long timestamp;
  unsigned long interval;
  HeartBeat* next = nullptr;
  HeartBeat* prev = nullptr;
  HeartBeat(unsigned long prev);
};

enum{
  IDLE,
  ADJUSTING,
  MEASURING
};

class HeartRate{
public:
  unsigned long heartRate;
  HeartBeat* heartBeats = nullptr;
  HeartBeat* heartBeatsTail = nullptr;
  int measurements[MEASUREMENTS_BUFFER_SIZE];
  float thresholdHigh = 0;
  float thresholdLow = 0;
  bool isPeak = false;
  int ampMin = 0;
  int ampMax = 0;
  int heartBeatsAmount = 0;
  int state = IDLE;
  short pin;
  HeartRate(short pin);
  ~HeartRate();
  int measure();
  void addHeartBeat();
  void popHeartBeat();
  void clearHeartBeats();
  void calculateThreshold();
  int calculateHeartbeat(); 
};