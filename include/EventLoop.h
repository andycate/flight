#pragma once

#include <Arduino.h>

#include <unordered_map>
#include <vector>
#include <functional>
#include <queue>

using namespace std;

class Subsystem;
class Comms;

typedef function<void(string,vector<float>)> EmitterFunc;
typedef function<void(int,vector<float>)> SenderFunc;

/**
 * Main event loop class.
 * 
 * This class ties all the subsystems and comms together,
 * combining the concept of a scheduler and an event queue
 * into one.
 */
class EventLoop {
  private:
    struct Packet {
      uint32_t when;
      int id;
      vector<float> args;
      Subsystem *s;

      bool operator >(const Packet& a) const {
        return when > a.when;
      }
      bool operator <(const Packet& a) const {
        return when < a.when;
      }
      bool operator ==(const Packet& a) const {
        return when == a.when;
      }
    };
    struct Event {
      uint32_t when;
      string event;
      vector<float> args;
      Subsystem *s;

      bool operator >(const Event& a) const {
        return when > a.when;
      }
      bool operator <(const Event& a) const {
        return when < a.when;
      }
      bool operator ==(const Event& a) const {
        return when == a.when;
      }
    };
    struct Task {
      uint32_t when;
      uint32_t period; // milliseconds between executions
      Subsystem *s;

      bool operator >(const Task& a) const {
        return when > a.when;
      }
      bool operator <(const Task& a) const {
        return when < a.when;
      }
      bool operator ==(const Task& a) const {
        return when == a.when;
      }
    };
    priority_queue<Packet, vector<Packet>, greater<Packet>> packetq;
    priority_queue<Event, vector<Event>, greater<Event>> eventq;
    priority_queue<Task, vector<Task>, greater<Task>> taskq;
    unordered_map<int,vector<Subsystem*>> packet_handlers;
    unordered_map<string,vector<Subsystem*>> event_handlers;
    vector<Comms*> comms;
    EmitterFunc emit_f;
    SenderFunc send_f;
    SenderFunc emit_packet_f;

    /**
     * Emit an event.
     * 
     * This finds all event handlers that respond to the named
     * event and queues them in the event queue. It is private,
     * because it is passed as a std::function object to Subsystems'
     * loop and handle_* functions.
     * 
     * @param string Name of the emitted event
     * @param args Arguments of the event
     */
    void emit(string event, vector<float> args);
    /**
     * Send a packet.
     * 
     * This queues a packet to send. It doesn't send the packet
     * synchronously, but queues a send task for each of the comms
     * subsystems.
     * 
     * @param id The id of the packet to send
     * @param args The packet contents
     */
    void send(int id, vector<float> args);
    /**
     * Emit a packet event.
     * 
     * This emits a packet event, queuing up all the packet handlers
     * that respond to this packet id. It's private, because it is
     * passed only to registered Comms class instances. This function
     * should only ever be called by the Comms class loop function.
     */
    void emit_packet(int id, vector<float> args);
  public:
    /**
     * Register a subsystem.
     * 
     * Adds the specified subsystem class instance to the task queue
     * with the specified update frequency. It also registers the
     * subsystem with the specified event handlers and packet handlers.
     * 
     * @param s A pointer to the subsystem to register. Should be called
     *          only from the constructor of the subsystem class.
     * @param events A list of events that this subsystem responds to
     * @param packets A list of packet ids that this subsystem responds to
     * @param rate The update frequency of this subsystem
     */
    void register_subsystem(Subsystem *s, vector<string> events, vector<int> packets, uint8_t rate);
    /**
     * Register a comms subsystem.
     * 
     * Registers an instance of the comms class, which is a special type of
     * subsystem that responds to packets waiting to be sent. It's loop
     * method gets called at the end of every EventLoop loop, and checks if
     * a packet is waiting to be received. If a packet is received, it parses
     * the packet and emits a packet event with the corresponding data received
     * in the packet.
     * 
     * @param c A pointer to the comms class instance
     */
    void register_comms(Comms *c);
    /**
     * Main event loop.
     * 
     * Runs the main event loop. Should be called repeatedly in a loop in
     * the main program thread. NOT THREAD SAFE.
     * 
     * The priority of the queues goes:
     * - packet queue
     * - event queue
     * - task queue
     * For a given queue to start being processed, the queues above it need
     * to be empty first.
     */
    void eloop();
    EventLoop();
};

class Subsystem {
  public:
    Subsystem();
    Subsystem(EventLoop *el, vector<string> events, vector<int> packets, uint8_t rate);
    virtual void handle_packet(int id, vector<float> args, EmitterFunc emit, SenderFunc send) = 0;
    virtual void handle_event(string event, vector<float> args, EmitterFunc emit, SenderFunc send) = 0;
    virtual void loop(EmitterFunc emit, SenderFunc send) = 0;
};

class Comms : public Subsystem {
  private:
    struct packet {
      int id;
      vector<float> values;
      uint16_t checksum;
    };
    uint16_t checksum(uint8_t *data, int count); // Fletcher16 checksum
    bool validate_packet(string raw_packet);
    packet decode_raw_packet(string raw_packet);
  protected:
    /**
     * Check for available packet.
     * 
     * @return whether a packet is waiting to be received and processed.
     */
    virtual bool packet_available() = 0;
    /**
     * Receives raw packet.
     * 
     * @return raw packet in string form
     */
    virtual string receive_raw_packet() = 0;
    /**
     * Send raw packet.
     * 
     * @param raw_packet The raw packet to be sent
     */
    virtual bool send_raw_packet(string raw_packet) = 0;
  public:
    Comms(EventLoop *el);
    /**
     * Handle packet event.
     * 
     * This function is special for the Comms class, and sends the specified
     * packet.
     */
    void handle_packet(int id, vector<float> args, EmitterFunc emit, SenderFunc send) override;
    /**
     * Handle registered events.
     * 
     * Should never be called for the comms class.
     */
    void handle_event(string event, vector<float> args, EmitterFunc emit, SenderFunc send) override;
    /**
     * Comms loop function.
     * 
     * Since the Comms class is special, this function gets called every
     * cycle of the event loop. It checks for incoming packets, and if one
     * is received, the send function is called.
     */
    void loop(EmitterFunc emit, SenderFunc send) override;
};
