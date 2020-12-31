#pragma once
#include "EventLoop.h"
#include "Comms.h"

#include <string>

class SerialComms : Comms {
  private:
    Stream *port;
    std::string receive_raw_packet();
    bool send_raw_packet(std::string raw_packet);
  public:
    SerialComms(EventLoop *el, Stream *port);
};
