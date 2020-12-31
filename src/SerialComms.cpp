#include "SerialComms.h"

SerialComms::SerialComms(EventLoop *el, Stream *port) :
  Comms(el), port(port) { Serial.begin(57600); init(); }

std::string SerialComms::receive_raw_packet() {
  while(Serial.available() == 0) {
    threads.yield();
  }
  return std::string(Serial.readStringUntil('\n').c_str());
}

// TODO: change this function to return false if fails?
bool SerialComms::send_raw_packet(std::string raw_packet) {
  Serial.println(raw_packet.c_str());
  return true;
}
