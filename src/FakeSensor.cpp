#include "sensors/FakeSensor.h"

#include <math.h>

FakeSensor::FakeSensor(uint32_t period, float amplitude) : period(period), amplitude(amplitude) {
  start_time = millis();
}

float FakeSensor::read(uint8_t channel) {
  uint32_t curr_time = millis();
  return (sin(((float)((curr_time - start_time) % period) + ((float)(channel * period) / 256.0)) * PI * 2.0 / (float)period) + 1.0) * amplitude;
}
