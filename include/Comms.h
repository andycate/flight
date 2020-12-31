#pragma once
#include "TeensyThreads.h"
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
    void handle(std::vector<float> args);
  protected:
    std::string receive_raw_packet();
    bool send_raw_packet(std::string raw_packet);
  public:
    Comms(EventLoop *el);
    void recv_loop();
    static void start_recv_loop(Comms *c);
};
