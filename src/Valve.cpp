#include "Valve.h"

Valve::Valve(EventLoop *el, DigitalInterface *di, uint8_t channel, int id)
  : Subsystem(el, {}, {id}, 0), di(di), channel(channel), id(id)
{
}

bool Valve::open() {
  return di->set_output(channel, 1);
}

bool Valve::close() {
  return di->set_output(channel, 0);
}

void Valve::handle_event(std::string event, std::vector<float> args) {}

void Valve::handle_packet(int id, std::vector<float> args) {
  bool success = (args[0]==1.0?open():close());
  if(success) {
    std::vector<float> data = {args[0], id};
    el->emit("send", data);
  }
}

void Valve::loop() {};
