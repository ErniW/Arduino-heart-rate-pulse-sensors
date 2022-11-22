#include "HeartBeats.h"

HeartBeats::HeartBeats(){};

HeartBeats::~HeartBeats(){
  clear();
}

void HeartBeats::push(){
  size++;

  if(!head){
    head = new HeartBeat(0);
    tail = head;
    return;
  }

  HeartBeat* temp = new HeartBeat(head->timestamp);
  temp->next = head;
  head->prev = temp;
  head = temp;
}

void HeartBeats::pop(){
  size--;

  HeartBeat* toRemove = tail;
  HeartBeat* temp = tail->prev;

  delete toRemove;
  tail = temp;
  tail->next = nullptr;
}

void HeartBeats::clear(){
  HeartBeat* current = head;

  while(current){
    HeartBeat* temp = current->next;
    delete current;
    current = current->next;
  }

  head = nullptr;
  size = 0;
}