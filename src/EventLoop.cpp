#include "EventLoop.h"

bool EventLoop::compare(event a, event b) {
  return a.when < b.when;
}

EventLoop::EventLoop() : pq(EventLoop::compare) {}

void EventLoop::emit(std::string e, std::vector<float> args) {
  while(eh_lock.try_lock() == 0) threads.yield();
  while(pq_lock.try_lock() == 0) threads.yield();
  if(handlers.count(e) == 0) {
    eh_lock.unlock();
    pq_lock.unlock();
    threads.yield();
  } else {
    for(EventHandler *eh : handlers.at(e)) {
      enqueue_unsafe(eh, args, 0);
    }
    eh_lock.unlock();
    pq_lock.unlock();
    threads.yield();
  }
}

void EventLoop::add_event_handler(std::string e, EventHandler *eh) {
  while(eh_lock.try_lock() == 0) threads.yield();
  if(handlers.count(e) == 0) {
    // insert
    handlers.insert({e, {eh}});
  } else {
    // modify
    handlers.at(e).push_back(eh);
  }
  eh_lock.unlock();
  threads.yield();
}

void EventLoop::enqueue_unsafe(EventHandler *eh, std::vector<float> args, uint32_t delay_ms) {
  event e;
  e.when = millis() + delay_ms;
  e.args = args;
  e.eh = eh;
  pq.push(e);
  has_event = true;
}

void EventLoop::enqueue(EventHandler *eh, std::vector<float> args, uint32_t delay_ms) {
  while(pq_lock.try_lock() == 0) threads.yield();
  enqueue_unsafe(eh, args, delay_ms);
  pq_lock.unlock();
  threads.yield();
}

void EventLoop::eloop() {
  while(1) {
    while(!has_event) threads.yield();
    while(pq_lock.try_lock() == 0) threads.yield();
    if(pq.isEmpty()) {
      has_event = false;
      pq_lock.unlock();
    } else {
      if(pq.peek().when <= millis()) {
        event next = pq.pop();
        pq_lock.unlock();
        // call function
        next.eh->handle(next.args);
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
