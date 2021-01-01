#pragma once
#include <vector>

class EventHandler {
  public:
    EventHandler() {};
    virtual void handle(std::vector<float> args) = 0;
};
