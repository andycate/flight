#pragma once
#include "Sensor.h"
#include "EventLoop.h"

#include <functional>
#include <vector>

class Measurement {
  private:
    EventLoop *el;
    Sensor *sensor;
    uint8_t channel;
    int packet;
    int rate;
    std::function<void(std::vector<float>)> handler;
  public:
    Measurement(EventLoop *el, Sensor *sensor, uint8_t channel, int packet, int rate);
    void publish(std::vector<float> arg);
};
