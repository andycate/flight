#pragma once
#include "Sensor.h"

class FakeSensor : public Sensor {
  private:
    uint32_t start_time;
    uint32_t period;
    float amplitude;
  public:
    FakeSensor(uint32_t period, float amplitude);
    float read(uint8_t channel) override;
};
