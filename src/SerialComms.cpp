#include "SerialComms.h"

SerialComms::SerialComms(EventLoop *el, Stream *port) :
  Comms(el), port(port) {}

std::string SerialComms::receive_raw_packet() {
  while(port->available() == 0) {
    threads.yield();
  }
  return std::string(port->readStringUntil('\n').c_str());
}

// TODO: change this function to return false if fails?
bool SerialComms::send_raw_packet(std::string raw_packet) {
  port->println(raw_packet.c_str());
  return true;
}
