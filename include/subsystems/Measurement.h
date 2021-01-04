#pragma once
#include "Subsystem.h"
#include "sensors/Sensor.h"

using namespace std;

class Measurement : public Subsystem {
  private:
    Sensor *s;
    uint8_t channel;
    int packet;
  public:
    Measurement(Sensor *s, uint8_t channel, int packet, uint8_t rate);
    void handle_packet(int id, vector<float> args, EmitterFunc emit, SenderFunc send);
    void handle_event(string event, vector<float> args, EmitterFunc emit, SenderFunc send);
    void loop(EmitterFunc emit, SenderFunc send);
};
