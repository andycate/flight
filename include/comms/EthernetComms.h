#pragma once
#include "Comms.h"

#include <Arduino.h>

#include <NativeEthernet.h>
#include <NativeEthernetUdp.h>

#include <string>

using namespace std;

class EthernetComms : public Comms {
  private:
    EthernetUDP Udp;
    unsigned int port; // try to find something that can be the same on gs
    IPAddress groundIP;
    IPAddress ip;

    string receive_raw_packet() override;
    bool send_raw_packet(string raw_packet) override;
    bool packet_available() override;
  public:
    /**
     * Construct a USB Serial comms subsystem.
     * 
     * @param port The usb serial port to connect to
     * @param baud the baud rate
     */
    EthernetComms(uint16_t port);
};
