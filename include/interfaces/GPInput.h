#pragma once
#include "DigitalInterface.h"

#include <Arduino.h>

class GPInput : public DigitalInterface {
  private:
    uint8_t pin;
    bool set_output(uint8_t channel, uint8_t state) override { return 0; };
  public:
    GPInput(uint8_t pin, bool pullup = true);
    uint8_t get_input(uint8_t channel) override;
};
