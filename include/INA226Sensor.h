#pragma once
#include "Sensor.h"
#include "DigitalInterface.h"

#include <i2c_device.h>

class INA226Sensor : Sensor {
  public:
    INA226Sensor(I2CMaster *bus, uint8_t address, DigitalInterface *alert);
    float read(uint8_t channel) override;
};
