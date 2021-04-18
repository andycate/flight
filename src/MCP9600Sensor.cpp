#include "sensors/MCP9600Sensor.h"

MCP9600Sensor::MCP9600Sensor(uint8_t address, _themotype type)
  : address(address), board()
{
    if(!board.begin(address)) {
        Serial.println("ERROR INITING BOARD " + address);
    }
    board.setADCresolution(MCP9600_ADCRESOLUTION_12);
    board.setThermocoupleType(type);
    board.setFilterCoefficient(3);
    board.enable(true);
}

float MCP9600Sensor::read(uint8_t channel) {
  Serial.println("read");
  return board.readThermocouple();
}
