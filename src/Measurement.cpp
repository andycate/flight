#include "Measurement.h"

Measurement::Measurement(EventLoop *el, Sensor *sensor, uint8_t channel, int packet, int rate)
  : el(el), sensor(sensor), channel(channel), packet(packet), rate(rate)
{
  handler = std::bind(&Measurement::publish, this, std::placeholders::_1);
  el->enqueue(handler, {}, 0);
}

void Measurement::publish(std::vector<float> arg) {
  float value = sensor->read(channel);
  el->emit("send", {value, packet});
  el->enqueue(handler, {}, 1000 / rate);
}
