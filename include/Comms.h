#pragma once
#include "EventLoop.h"
#include "EventHandler.h"

#include <string>
#include <vector>

class Comms : EventHandler {
  private:
    struct packet {
      int id;
      std::vector<float> values;
      uint16_t checksum;
    };
    EventLoop *el;
    uint16_t checksum(uint8_t *data, int count); // Fletcher16 checksum
    bool validate_packet(std::string raw_packet);
    packet decode_raw_packet(std::string raw_packet);
  protected:
    virtual bool packet_available() = 0;
    virtual std::string receive_raw_packet() = 0;
    virtual bool send_raw_packet(std::string raw_packet) = 0;
  public:
    Comms(EventLoop *el);
    void rloop(); // checks if there are pending messages at the end of each loop
    void handle(std::vector<float> args);
};
