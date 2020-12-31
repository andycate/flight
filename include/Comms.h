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
  protected:
    virtual std::string receive_raw_packet();
    virtual bool send_raw_packet(std::string raw_packet);
    void init(); // should be called in constructor of child after child init
  public:
    Comms(EventLoop *el);
    void recv_loop();
    static void start_recv_loop(Comms *c);
    void handle(std::vector<float> args);
};
