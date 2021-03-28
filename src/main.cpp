#include "EventLoop.h"
#include "comms/USBSerialComms.h"
#include "interfaces/GPInput.h"
#include "interfaces/GPIOutput.h"
#include "sensors/ADS1219Sensor.h"
#include "sensors/INA226Sensor.h"
#include "sensors/MCP9600Sensor.h"
#include "subsystems/Measurement.h"
#include "subsystems/Valve.h"
#include "subsystems/Heater.h"

#include <Arduino.h>
#include <i2c_device.h>

int main(int argc, char**argv) {
  Serial.begin(57600);
  EventLoop el;

  // /* PACKET DEFINITIONS */
  enum Telemetry {
    TC1 = 0,
    TC2 = 1,
    TC3 = 2,
    HEAT1 = 10,
    HEAT2 = 11,
    HEAT3 = 12,
  };

  Wire.begin();

  /* INTERFACE DEFINITIONS */
  GPIOutput gpio0(0);
  GPIOutput gpio1(1);
  GPIOutput gpio2(2);
  // GPIOutput gpio3(3);
  // GPIOutput gpio4(4);
  // GPIOutput gpio5(5);
  // GPIOutput gpio6(6);
  // GPIOutput gpio7(7);
  // GPInput gpio23(23, true);
  // GPInput gpio28(28, true);
  // GPInput gpio29(29, true);
  // I2CMaster &i2c0 = Master;
  // i2c0.begin(100 * 1000U); // 100 kHz I2C bus. Change to 100 kHz or lower if using long wires

  /* HARDWARE DEFINITIONS */
  // ADS1219Sensor adc0(&i2c0, 0x4A, &gpio29);
  // ADS1219Sensor adc1(&i2c0, 0x48, &gpio28);
  // INA226Sensor pwr0(&i2c0, 0x40, &gpio23, 0.002, 4.0, true);
  MCP9600Sensor tc1(0x60, MCP9600_TYPE_K);
  // MCP9600Sensor tc2(0x67, MCP9600_TYPE_K);
  MCP9600Sensor tc2(0x62, MCP9600_TYPE_K);
  MCP9600Sensor tc3(0x64, MCP9600_TYPE_K);

  /* SUBSYSTEM DEFINITIONS */
  // Measurement lox_tank(el, adc0, 0, LOX_TANK); // event loop, device, channel, packet id
  // Measurement prop_tank(el, adc0, 1, PROP_TANK);
  // Measurement lox_inj(el, adc0, 2, LOX_INJ);
  // Measurement prop_inj(el, adc0, 3, LOX_INJ);
  // Measurement nitrogen(el, adc1, 0, NITROGEN);

  // Measurement voltage(&pwr0, 0, VOLTAGE, 5); el.adds(&voltage);
  // Measurement current(&pwr0, 1, CURRENT, 5); el.adds(&current);
  // Measurement wattage(&pwr0, 2, WATTAGE, 5); el.adds(&wattage);
  Measurement m_tc1(&tc1, 0, TC1, 5); el.adds(&m_tc1);
  // Measurement m_tc2(&tc2, 0, TC2, 5); el.adds(&m_tc2);
  Measurement m_tc2(&tc2, 0, TC2, 5); el.adds(&m_tc2);
  Measurement m_tc3(&tc3, 0, TC3, 5); el.adds(&m_tc3);

  Heater h1(&gpio0, 0, HEAT1); el.adds(&h1);
  Heater h2(&gpio1, 0, HEAT2); el.adds(&h2);
  Heater h3(&gpio2, 0, HEAT3); el.adds(&h3);
  // Valve lox_tway(&gpio0, 0, LOX_TWAY); el.adds(&lox_tway);
  // Valve prop_tway(&gpio1, 0, PROP_TWAY); el.adds(&prop_tway);
  // Valve lox_fway(&gpio2, 0, LOX_FWAY); el.adds(&lox_fway);
  // Valve prop_fway(&gpio3, 0, PROP_FWAY); el.adds(&prop_fway);
  // Valve lox_gems(&gpio4, 0, LOX_GEMS); el.adds(&lox_gems);
  // Valve prop_gems(&gpio5, 0, PROP_GEMS); el.adds(&prop_gems);
  // Valve hps(&gpio6, 0, HPS); el.adds(&hps);

  // COMM DEFINITION
  
  USBSerialComms comms(&Serial, 57600); el.addc(&comms);

  while(1) {
    el.eloop();
    yield(); // does this need to be here?
  }
  return 0;
}
