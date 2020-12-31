#include "EventLoop.h"

bool EventLoop::compare(event a, event b) {
  return a.when < b.when;
}

EventLoop::EventLoop() : pq(EventLoop::compare) {}

bool EventLoop::emit(std::string e, std::vector<float> args) {
  return true;
}

void EventLoop::add_event_handler(std::string e, void (EventHandler::*handler)(std::vector<float> args)) {

}

void EventLoop::enqueue(void (*func)(), uint32_t delay_ms) {
  event e;
  e.func = func;
  e.when = millis() + delay_ms;
  while(pq_lock.try_lock() == 0) {
    threads.yield();
  }
  pq.push(e);
  pq_lock.unlock();
  has_event = true;
  threads.yield();
}

void EventLoop::eloop() {
  while(1) {
    while(!has_event) {
      threads.yield();
    }

    while(pq_lock.try_lock() == 0) {
      threads.yield();
    }
    if(pq.isEmpty()) {
      has_event = false;
      pq_lock.unlock();
    } else {
      if(pq.peek().when <= millis()) {
        event next = pq.pop();
        pq_lock.unlock();
        // call function
        next.func();
      } else {
        pq_lock.unlock();
      }
    }
    threads.yield();
  }
}

void EventLoop::static_eloop(EventLoop *el) {
  el->eloop();
}

void EventLoop::start_eloop() {
  threads.addThread(EventLoop::static_eloop, this);
}
