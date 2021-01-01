#include "Valve.h"

Valve::Valve(EventLoop *el, DigitalInterface *di, uint8_t channel, int id)
  : el(el), di(di), channel(channel), id(id)
{
  el->add_event_handler("recv"+id, this);
}

bool Valve::open() {
  return di->set_output(channel, 1);
}

bool Valve::close() {
  return di->set_output(channel, 0);
}

void Valve::handle(std::vector<float> args) {
  bool success = (args[0]==1.0?open():close());
  if(success) {
    el->emit("send", {args[0], id});
  }
}
