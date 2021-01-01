#pragma once
#include "PriorityQueue.h"
#include "EventHandler.h"

#include <unordered_map>
#include <vector>
#include <functional>

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
    std::vector<std::function<void()>> loopers;
  public:
    void enqueue(EventHandler *eh, std::vector<float> args, uint32_t delay_ms);
    void emit(std::string e, std::vector<float> args);
    void add_event_handler(std::string e, EventHandler *eh);
    void add_looper(std::function<void()> func);
    void eloop();
    EventLoop();
};
