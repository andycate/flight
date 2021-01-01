#pragma once
#include "PriorityQueue.h"
#include "EventHandler.h"

#include <unordered_map>
#include <vector>

class EventLoop {
  private:
    struct event {
      uint32_t when;
      std::vector<float> args;
      EventHandler *eh;
    };
    static bool compare(event a, event b);
    PriorityQueue<event> pq;
    std::unordered_map<std::string,std::vector<EventHandler*>> handlers;
  public:
    void enqueue(EventHandler *eh, std::vector<float> args, uint32_t delay_ms);
    void emit(std::string e, std::vector<float> args);
    void add_event_handler(std::string e, EventHandler *eh);
    void eloop();
    EventLoop();
};
