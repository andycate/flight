#pragma once
#include "Subsystem.h"
#include "interfaces/DigitalInterface.h"

class Heater : public Subsystem {
  private:
    DigitalInterface *di;
    uint8_t channel;
    int id;
    uint32_t ontime;
    uint32_t last_time;
  public:
    /**
     * Construct a valve object.
     * 
     * @param di The digital interface that the valve is behind
     * @param channel The channel of the digital interface that the valve is on
     * @param id The id of the packet to listen for
     */
    Heater(DigitalInterface *di, uint8_t channel, int id);
    void handle_packet(int id, vector<float> args, EmitterFunc emit, SenderFunc send) override;
    void handle_event(string event, vector<float> args, EmitterFunc emit, SenderFunc send) override;
    void loop(EmitterFunc emit, SenderFunc send) override;
};
