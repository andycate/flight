#pragma once
#include "Subsystem.h"
#include "Comms.h"

#include <Arduino.h>

#include <unordered_map>
#include <vector>
#include <functional>
#include <queue>

using namespace std;

typedef function<void(string,vector<float>)> EmitterFunc;
typedef function<void(int,vector<float>)> SenderFunc;

/**
 * Main event loop class
 * 
 * This class ties all the subsystems and comms together,
 * combining the concept of a scheduler and an event queue
 * into one.
 */
class EventLoop {
  private:
    struct Task {
      uint32_t when;
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
    struct Event {
      uint32_t when;
      std::string event;
      std::vector<float> args;
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
    struct Packet {
      uint32_t when;
      int id;
      std::vector<float> args;
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
    priority_queue<Task, vector<Task>, greater<Task>> taskq;
    priority_queue<Event, vector<Event>, greater<Event>> eventq;
    priority_queue<Packet, vector<Packet>, greater<Packet>> packetq;
    unordered_map<string,vector<Subsystem*>> event_handlers;
    unordered_map<int,vector<Subsystem*>> packet_handlers;
    vector<Comms*> comms;

    /**
     * Emit an event
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
     * Send a packet
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
     * Emit a packet event
     * 
     * This emits a packet event, queuing up all the packet handlers
     * that respond to this packet id. It's private, because it is
     * passed only to registered Comms class instances. This function
     * should only ever be called by the Comms class loop function.
     */
    void emit_packet(int id, vector<float> args);
  public:
    /**
     * Register a subsystem
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
     * Register a comms subsystem
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
     * Main event loop
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
