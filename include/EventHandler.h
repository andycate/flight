#pragma once
#include <vector>

class EventHandler {
  protected:
    void handle(std::vector<float> args) {}
  public:
    EventHandler() {};
};
