#pragma once
#include "Arduino.h"

#define MEASUREMENTS_BUFFER_SIZE 50
#define HEARTBEATS_BUFFER_SIZE 10

struct HeartBeat {
  unsigned long timestamp;
  unsigned long interval;
  int id;
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
  float threshold = 0;
  int ampMin = 0;
  int ampMax = 0;
  int maxHeartBeats = HEARTBEATS_BUFFER_SIZE;
  int heartBeatsAmount = 0;
  int state = IDLE;
  short pin;
  HeartRate(short pin);
  ~HeartRate();
  int measure();
  void addHeartBeat();
  void popHeartBeat();
  void calculateThreshold();
  void calculateHeartbeat(); 
};