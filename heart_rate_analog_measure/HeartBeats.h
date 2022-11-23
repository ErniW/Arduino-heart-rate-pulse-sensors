#pragma once

#define HEARTBEATS_BUFFER_SIZE 10

struct HeartBeat {
  unsigned long timestamp;
  unsigned long interval;
  HeartBeat* next = nullptr;
  HeartBeat* prev = nullptr;
  HeartBeat(unsigned long prev);
};

class HeartBeats{
public:
  HeartBeats();
  ~HeartBeats();
  HeartBeat* head = nullptr;
  HeartBeat* tail = nullptr;
  int size = 0;
  void push();
  void pop();
  void clear();
  bool isFull();
};