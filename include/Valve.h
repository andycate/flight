#pragma once
#include "EventLoop.h"
#include "EventHandler.h"
#include "DigitalInterface.h"

#include <vector>

class Valve : EventHandler {
  private:
    EventLoop *el;
    DigitalInterface *di;
    uint8_t channel;
    int id;
  public:
    Valve(EventLoop *el, DigitalInterface *di, uint8_t channel, int id);
    void handle(std::vector<float> args) override;
    bool open();
    bool close();
};
