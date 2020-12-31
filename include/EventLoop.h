#pragma once
#include "PriorityQueue.h"
#include "TeensyThreads.h"
#include "EventHandler.h"

#include <unordered_map>
#include <vector>

class EventLoop {
  private:
    struct event {
      uint32_t when;
      void (*func)();
    };
    struct handler {
      void (EventHandler::*func)();
    };
    static bool compare(event a, event b);
    volatile bool has_event = false;
    PriorityQueue<event> pq;
    Threads::Mutex pq_lock;
    std::unordered_map<std::string,std::vector<handler>> handlers;
  public:
    void enqueue(void (*func)(), uint32_t delay_ms);
    bool emit(std::string e, std::vector<float> args);
    void add_event_handler(std::string e, void (EventHandler::*handler)(std::vector<float> args));
    void eloop();
    void start_eloop();
    static void static_eloop(EventLoop *el);
    EventLoop();
};
