#pragma once
#include "EventLoop.h"
#include "Comms.h"

#include <string>

class HardwareSerialComms : public Comms {
  private:
    HardwareSerial *port;
    std::string receive_raw_packet() override;
    bool send_raw_packet(std::string raw_packet) override;
    bool packet_available() override;
  public:
    HardwareSerialComms(EventLoop *el, HardwareSerial *port, int baud);
};
