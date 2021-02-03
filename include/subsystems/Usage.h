#pragma once
#include "EventLoop.h"
#include "subsystems/Subsystem.h"

class Usage : public Subsystem {
  private:
    EventLoop *el;
  public:
    Usage(EventLoop *el) : Subsystem({}, {}, 1), el(el) {}
    void handle_packet(int id, vector<float> args, EmitterFunc emit, SenderFunc send) {}
    void handle_event(string event, vector<float> args, EmitterFunc emit, SenderFunc send) {}
    void loop(EmitterFunc emit, SenderFunc send) {
      send(40, {100.0*(float)el->run_time/(float)(el->idle_time+el->run_time)});
      el->idle_time = 0;
      el->run_time = 0;
    }
};
