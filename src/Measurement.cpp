#include "Measurement.h"

Measurement::Measurement(EventLoop *el, Sensor *sensor, uint8_t channel, int packet, uint8_t rate)
  : Subsystem(el, {}, rate), sensor(sensor), channel(channel), packet(packet), rate(rate)
{
}

void Measurement::loop() {
  float value = sensor->read(channel);
  el->emit("send", {value, packet});
  el->enqueue(handler, {}, 1000 / rate);
}

void Measurement::handle(std::string event, std::vector<float> args) {}
