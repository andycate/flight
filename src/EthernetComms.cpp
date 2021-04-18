#include "comms/EthernetComms.h"

EthernetComms::EthernetComms(uint16_t port) : Comms(), groundIP(10, 0, 0, 69), ip(10, 0, 0, 178), port(port) {
  byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

  Ethernet.begin(mac, ip);

  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    Serial.flush();
    exit(1);
  } else if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
    Serial.flush();
    exit(1);
  }

  Udp.begin(port);
}

bool EthernetComms::packet_available() {
  return Udp.parsePacket();
}

string EthernetComms::receive_raw_packet() {
    IPAddress remote = Udp.remoteIP();
    char command[75];
    for (int i=0; i < 4; i++) {
        Serial.print(remote[i], DEC);
        if (i < 3) {
            Serial.print(".");
        }
    }
    if(Udp.remoteIP() == groundIP) {
        // receivedCommand = true;
        Udp.read(command, 75);
    }

    return string(command);
}

// TODO: change this function to return false if fails? Maybe flush serial?
bool EthernetComms::send_raw_packet(string raw_packet) {
  Udp.beginPacket(groundIP, port);
  Udp.write(raw_packet.c_str());
  Udp.endPacket();
  return true;
}
