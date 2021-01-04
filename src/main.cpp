#include "EventLoop.h"
#include "comms/USBSerialComms.h"
#include "interfaces/GPIOutput.h"
#include "sensors/INA226Sensor.h"
#include "subsystems/Valve.h"

#include <Arduino.h>
#include <i2c_device.h>

int main(int argc, char**argv) {
  EventLoop el;

  // /* PACKET DEFINITIONS */
  enum Telemetry {
    LOX_TANK = 0,
    PROP_TANK = 1,
    LOX_INJ = 2,
    PROP_INJ = 3,
    NITROGEN = 4,
    VOLTAGE = 5,
    CURRENT = 6,
    WATTAGE = 7,

    LOX_TWAY = 10,
    PROP_TWAY = 11,
    LOX_FWAY = 12,
    PROP_FWAY = 13,
    LOX_GEMS = 14,
    PROP_GEMS = 15,
    HPS = 16,
  };

  // /* INTERFACE DEFINITIONS */
  GPIOutput gpio0(0);
  GPIOutput gpio1(1);
  GPIOutput gpio2(2);
  GPIOutput gpio3(3);
  GPIOutput gpio4(4);
  GPIOutput gpio5(5);
  GPIOutput gpio6(6);
  GPIOutput gpio7(7);
  // GPInput gpio23(23, true);
  // GPInput gpio28(28, true);
  // GPInput gpio29(29, true);
  I2CMaster &i2c0 = Master;
  i2c0.begin(400 * 1000U);

  // /* HARDWARE DEFINITIONS */
  // ADS1219Sensor adc0(&i2c0, 0x4A, &gpio29);
  // ADS1219Sensor adc1(&i2c0, 0x48, &gpio28);
  INA226Sensor pwr0(&i2c0, 0x40, &gpio23, 0.002, 4.0, true);

  // /* SUBSYSTEM DEFINITIONS */
  // Measurement lox_tank(el, adc0, 0, LOX_TANK); // event loop, device, channel, packet id
  // Measurement prop_tank(el, adc0, 1, PROP_TANK);
  // Measurement lox_inj(el, adc0, 2, LOX_INJ);
  // Measurement prop_inj(el, adc0, 3, LOX_INJ);
  // Measurement nitrogen(el, adc1, 0, NITROGEN);

  // Measurement voltage(&el, &pwr0, 0, VOLTAGE, 10);
  // Measurement current(&el, &pwr0, 1, CURRENT, 10);
  // Measurement wattage(&el, &pwr0, 2, WATTAGE, 10);

  Valve lox_tway(&gpio0, 0, LOX_TWAY); el.adds(&lox_tway);
  Valve prop_tway(&gpio1, 0, PROP_TWAY); el.adds(&prop_tway);
  Valve lox_fway(&gpio2, 0, LOX_FWAY); el.adds(&lox_fway);
  Valve prop_fway(&gpio3, 0, PROP_FWAY); el.adds(&prop_fway);
  Valve lox_gems(&gpio4, 0, LOX_GEMS); el.adds(&lox_gems);
  Valve prop_gems(&gpio5, 0, PROP_GEMS); el.adds(&prop_gems);
  Valve hps(&gpio6, 0, HPS); el.adds(&hps);

  /* COMM DEFINITION */
  USBSerialComms comms(&Serial, 57600); el.addc(&comms);

  while(1) {
    el.eloop();
    yield(); // does this need to be here?
  }
  return 0;
}
