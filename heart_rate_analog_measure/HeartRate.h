#pragma once
#include "Arduino.h"

#define MEASUREMENTS_BUFFER_SIZE 50
#define HEARTBEATS_BUFFER_SIZE 10

struct Heartbeat {
  unsigned long timestamp;
  int id;
};

enum{
  IDLE,
  ADJUSTING,
  MEASURING
};

class HeartRate{
public:
  int heartRate;
  Heartbeat* heartBeats;
  int measurements[MEASUREMENTS_BUFFER_SIZE];
  int threshold;
  int ampMin;
  int ampMax;
  int maxMeasurements;
  int state;
  HeartRate();
  int measure();
  void addHeartBeat();
  void popHeartBeat();
  int calculateThreshold();
  int calculateHeartbeat(); 
};