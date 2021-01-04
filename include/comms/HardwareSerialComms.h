#pragma once
#include "comms/Comms.h"

#include <string>

using namespace std;

class HardwareSerialComms : public Comms {
  private:
    HardwareSerial *port;
    string receive_raw_packet() override;
    bool send_raw_packet(string raw_packet) override;
    bool packet_available() override;
  public:
    HardwareSerialComms(HardwareSerial *port, int baud);
};
