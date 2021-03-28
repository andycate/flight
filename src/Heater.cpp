#include "subsystems/Heater.h"

Heater::Heater(DigitalInterface *di, uint8_t channel, int id)
  : Subsystem({}, {id}, 100), di(di), channel(channel), id(id), ontime(0.0)
{
  last_time = millis();
}

void Heater::handle_packet(int id, vector<float> args, EmitterFunc emit, SenderFunc send) {
  ontime = args[0] * 1000;
}

void Heater::handle_event(string event, vector<float> args, EmitterFunc emit, SenderFunc send) {}

void Heater::loop(EmitterFunc emit, SenderFunc send) {
  uint32_t now = millis();
  if(now - last_time > ontime) {
    di->set_output(channel, 0);
  } else {
    di->set_output(channel, 1);
  }
  if(now - last_time > 1000) {
    last_time = now;
  }
}
