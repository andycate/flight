#pragma once
#include "Subsystem.h"
#include "interfaces/DigitalInterface.h"

class Valve : public Subsystem {
  private:
    DigitalInterface *di;
    uint8_t channel;
    int id;
  public:
    Valve(DigitalInterface *di, uint8_t channel, int id);
    void handle_packet(int id, vector<float> args, EmitterFunc emit, SenderFunc send) override;
    void handle_event(string event, vector<float> args, EmitterFunc emit, SenderFunc send) override;
    void loop(EmitterFunc emit, SenderFunc send) override;
};
