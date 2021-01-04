#include "Subsystem.h"

// if rate is set to 0, the loop fn will be ignored
Subsystem::Subsystem(EventLoop *el, std::vector<std::string> events, std::vector<int> packets, uint8_t rate)
  : el(el)
{
  el->register_subsystem(this, events, packets, rate);
}
