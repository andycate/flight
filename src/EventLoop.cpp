#include "EventLoop.h"

bool EventLoop::compare(event a, event b) {
  return a.when < b.when;
}

EventLoop::EventLoop() : pq(EventLoop::compare) {}

void EventLoop::emit(std::string e, void *arg) {
  if(handlers.count(e) != 0) {
    for(EventHandler eh : handlers.at(e)) {
      enqueue(eh, arg, 0);
    }
  }
}

void EventLoop::add_event_handler(std::string e, EventHandler eh) {
  if(handlers.count(e) == 0) {
    // insert
    handlers.insert({e, {eh}});
  } else {
    // modify
    handlers.at(e).push_back(eh);
  }
}

void EventLoop::add_looper(Looper func) {
  loopers.push_back(func);
}

void EventLoop::enqueue(EventHandler eh, void *arg, uint32_t delay_ms) {
  event e;
  e.when = millis() + delay_ms;
  e.arg = arg;
  e.eh = eh;
  pq.push(e);
}

void EventLoop::eloop() {
  while(1) {
    if(!pq.isEmpty()) {
      if(pq.peek().when <= millis()) {
        event next = pq.pop();
        // call function
        next.eh(next.arg);
      } else {
        return;
      }
    }
    for(Looper func : loopers) {
      func();
    }
  }
}
