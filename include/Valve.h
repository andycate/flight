#pragma once
#include "EventLoop.h"
#include "DigitalInterface.h"

#include <vector>

class Valve {
  private:
    EventLoop *el;
    DigitalInterface *di;
    uint8_t channel;
    int id;
  public:
    Valve(EventLoop *el, DigitalInterface *di, uint8_t channel, int id);
    void handle(void *arg);
    bool open();
    bool close();
};
