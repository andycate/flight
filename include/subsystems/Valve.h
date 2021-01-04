#pragma once
#include "Subsystem.h"
#include "EventLoop.h"
#include "DigitalInterface.h"

#include <vector>

using namespace std;

class Valve : public Subsystem {
  private:
    EventLoop *el;
    DigitalInterface *di;
    uint8_t channel;
    int id;
  public:
    Valve(EventLoop *el, DigitalInterface *di, uint8_t channel, int id);
    void handle_event(string event, vector<float> args, EmitterFunc emit, SenderFunc send) override;
    void handle_packet(string event, vector<float> args, EmitterFunc emit, SenderFunc send) override;
    void loop(EmitterFunc emit, SenderFunc send) override;
    bool open();
    bool close();
};
