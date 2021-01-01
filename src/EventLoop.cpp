#include "EventLoop.h"

uint32_t FreeRam(){ // for Teensy 3.0
  uint32_t stackTop;
  uint32_t heapTop;

  // current position of the stack.
  stackTop = (uint32_t) &stackTop;

  // current position of heap.
  void* hTop = malloc(1);
  heapTop = (uint32_t) hTop;
  free(hTop);

  // The difference is the free, available ram.
  return stackTop - heapTop;
}

EventLoop::EventLoop() {}

void EventLoop::emit(std::string e, EventArg arg) {
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

void EventLoop::enqueue(EventHandler eh, EventArg arg, uint32_t delay_ms) {
  Event e;
  e.when = millis() + delay_ms;
  e.arg = arg;
  e.eh = eh;
  pq.push(e);
}

void EventLoop::eloop() {
  while(1) {
    if(!pq.empty()) {
      if(pq.top().when <= millis()) {
        Event next = pq.top();
        pq.pop();
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
