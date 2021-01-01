#include "Valve.h"

Valve::Valve(EventLoop *el, DigitalInterface *di, uint8_t channel, int id)
  : el(el), di(di), channel(channel), id(id)
{
  el->add_event_handler("recv"+id, std::bind(&Valve::handle, this, std::placeholders::_1));
}

bool Valve::open() {
  return di->set_output(channel, 1);
}

bool Valve::close() {
  return di->set_output(channel, 0);
}

void Valve::handle(void *arg) {
  std::vector<float> args = *(std::vector<float> *) arg;
  bool success = (args[0]==1.0?open():close());
  if(success) {
    std::vector<float> data = {args[0], id};
    el->emit("send", &data);
  }
}
