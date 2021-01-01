#include "EventLoop.h"
#include "USBSerialComms.h"
#include "Valve.h"
#include "GPIOutput.h"
#include "GPInput.h"
#include "ADS1219Sensor.h"
#include "INA226Sensor.h"

#include <Arduino.h>
#include <i2c_device.h>

int main(int argc, char**argv) {
  delay(2000);
  Serial.println("Start");

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
  GPInput gpio23(23, true);
  GPInput gpio28(28, true);
  GPInput gpio29(29, true);
  I2CMaster &i2c0 = Master;
  i2c0.begin(400 * 1000U);
  Serial.println("after");

  // /* HARDWARE DEFINITIONS */
  // ADS1219Sensor adc0(&i2c0, 0x4A, &gpio29);
  // ADS1219Sensor adc1(&i2c0, 0x48, &gpio28);
  // INA226Sensor pwr0(&i2c0, 0x40, &gpio23);

  // /* SUBSYSTEM DEFINITIONS */
  // Measurement lox_tank(el, adc0, 0, LOX_TANK); // event loop, device, channel, packet id
  // Measurement prop_tank(el, adc0, 1, PROP_TANK);
  // Measurement lox_inj(el, adc0, 2, LOX_INJ);
  // Measurement prop_inj(el, adc0, 3, LOX_INJ);
  // Measurement nitrogen(el, adc1, 0, NITROGEN);

  // Measurement voltage(el, pwr0, 0, VOLTAGE);
  // Measurement current(el, pwr0, 1, CURRENT);
  // Measurement wattage(el, pwr0, 2, WATTAGE);

  Valve lox_tway(&el, &gpio0, 0, LOX_TWAY);
  Valve prop_tway(&el, &gpio1, 0, PROP_TWAY);
  Valve lox_fway(&el, &gpio2, 0, LOX_FWAY);
  Valve prop_fway(&el, &gpio3, 0, PROP_FWAY);
  Valve lox_gems(&el, &gpio4, 0, LOX_GEMS);
  Valve prop_gems(&el, &gpio5, 0, PROP_GEMS);
  Valve hps(&el, &gpio6, 0, HPS);

  /* COMM DEFINITION */
  USBSerialComms comms(&el, &Serial, 57600);

  while(1) {
    el.eloop();
    yield(); // does this need to be here?
  }
  return 0;
}
