#pragma once
#include "Sensor.h"
#include "interfaces/DigitalInterface.h"

#include <i2c_device.h>
#include <Adafruit_MCP9600.h>

class MCP9600Sensor : public Sensor {
  private:
    uint8_t address;
    Adafruit_MCP9600 board;
  public:
    MCP9600Sensor(uint8_t address, _themotype type);
    float read(uint8_t channel) override;
};
