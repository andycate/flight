#pragma once
#include "EventLoop.h"
#include "Comms.h"

#include <string>

class USBSerialComms : public Comms {
  private:
    usb_serial_class *port;
    std::string receive_raw_packet() override;
    bool send_raw_packet(std::string raw_packet) override;
    bool packet_available() override;
  public:
    USBSerialComms(EventLoop *el, usb_serial_class *port, int baud);
};
