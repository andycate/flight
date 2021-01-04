#pragma once
#include "EventLoop.h"

using namespace std;

class Subsystem {
  protected:
    EventLoop *el;
  public:
    Subsystem(EventLoop *el, vector<string> events, vector<int> packets, uint8_t rate);
    virtual void handle_event(string event, vector<float> args, EmitterFunc emit, SenderFunc send) = 0;
    virtual void handle_packet(string event, vector<float> args, EmitterFunc emit, SenderFunc send) = 0;
    virtual void loop(EmitterFunc emit, SenderFunc send) = 0;
};
