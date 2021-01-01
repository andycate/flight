#pragma once
#include "PriorityQueue.h"

#include <unordered_map>
#include <vector>
#include <functional>

typedef std::function<void(void*)> EventHandler;
typedef std::function<void()> Looper;
class EventLoop {
  private:
    struct event {
      uint32_t when;
      void *arg;
      EventHandler eh;
    };
    static bool compare(event a, event b);
    PriorityQueue<event> pq;
    std::unordered_map<std::string,std::vector<EventHandler>> handlers;
    std::vector<Looper> loopers;
  public:
    void enqueue(EventHandler eh, void *arg, uint32_t delay_ms);
    void emit(std::string e, void *arg);
    void add_event_handler(std::string e, EventHandler eh);
    void add_looper(Looper func);
    void eloop();
    EventLoop();
};
