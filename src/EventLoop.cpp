#include "EventLoop.h"

bool EventLoop::compare(event a, event b) {
  return a.when < b.when;
}

EventLoop::EventLoop() : pq(EventLoop::compare) {}

void EventLoop::emit(std::string e, std::vector<float> args) {
  if(handlers.count(e) == 0) {
    return;
  } else {
    for(EventHandler *eh : handlers.at(e)) {
      enqueue(eh, args, 0);
    }
  }
}

void EventLoop::add_event_handler(std::string e, EventHandler *eh) {
  if(handlers.count(e) == 0) {
    // insert
    handlers.insert({e, {eh}});
  } else {
    // modify
    handlers.at(e).push_back(eh);
  }
}

void EventLoop::enqueue(EventHandler *eh, std::vector<float> args, uint32_t delay_ms) {
  event e;
  e.when = millis() + delay_ms;
  e.args = args;
  e.eh = eh;
  pq.push(e);
}

void EventLoop::eloop() {
  while(1) {
    if(pq.isEmpty()) {
      return;
    } else {
      if(pq.peek().when <= millis()) {
        event next = pq.pop();
        // call function
        next.eh->handle(next.args);
      } else {
        return;
      }
    }
  }
}
