#pragma once
#include "Sensor.h"
#include "EventLoop.h"
#include "Subsystem.h"

#include <functional>
#include <vector>

class Measurement : public Subsystem {
  private:
    Sensor *sensor;
    uint8_t channel;
    int packet;
    std::function<void(std::vector<float>)> handler;
  public:
    Measurement(EventLoop *el, Sensor *sensor, uint8_t channel, int packet, uint8_t rate);
    void loop() override;
    void handle(std::string event, std::vector<float> args) override;
};
