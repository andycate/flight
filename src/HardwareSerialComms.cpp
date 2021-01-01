#include "HardwareSerialComms.h"

HardwareSerialComms::HardwareSerialComms(EventLoop *el, HardwareSerial *port, int baud) :
  Comms(el), port(port) { port->begin(baud); }

bool HardwareSerialComms::packet_available() {
  return port->available() > 0;
}

std::string HardwareSerialComms::receive_raw_packet() {
  return std::string(port->readStringUntil('\n').c_str());
}

// TODO: change this function to return false if fails? Maybe flush serial?
bool HardwareSerialComms::send_raw_packet(std::string raw_packet) {
  port->println(raw_packet.c_str());
  return true;
}
