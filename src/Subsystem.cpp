#include "EventLoop.h"

// if rate is set to 0, the loop fn will be ignored
Subsystem::Subsystem(EventLoop *el, vector<string> events, vector<int> packets, uint8_t rate)
{
  el->register_subsystem(this, events, packets, rate);
}

Subsystem::Subsystem() {}
