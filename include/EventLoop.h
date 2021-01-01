#pragma once
#include <Arduino.h>

#include <unordered_map>
#include <vector>
#include <functional>
#include <queue>

typedef std::vector<float> EventArg;
typedef std::function<void(EventArg)> EventHandler;
typedef std::function<void()> Looper;
class EventLoop {
  private:
    struct Event {
      uint32_t when;
      EventArg arg;
      EventHandler eh;

      bool operator >(const Event& a) const {
        return a.when > when;
      }
      bool operator <(const Event& a) const {
        return a.when < when;
      }
      bool operator ==(const Event& a) const {
        return a.when == when;
      }
    };
    std::priority_queue<Event, std::vector<Event>, std::greater<Event>> pq;
    std::unordered_map<std::string,std::vector<EventHandler>> handlers;
    std::vector<Looper> loopers;
  public:
    void enqueue(EventHandler eh, EventArg arg, uint32_t delay_ms);
    void emit(std::string e, EventArg arg);
    void add_event_handler(std::string e, EventHandler eh);
    void add_looper(Looper func);
    void eloop();
    EventLoop();
};
