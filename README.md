# flight
This is an experimental codebase with an EventQueue/Scheduler
architecture for rocket control. The ideafor using this architecture
is the ease of configuring flight hardware on the go.

## Overview
All configuration is done in the `main.cpp` file. First the
main EventLoop object is defined. Then, Interfaces and Sensors
are defined. Next, Subsystems are defined and added to the
EventLoop. Finally, Comms classes are defined and added to the
EventLoop.

At the end of the `main` function, the `EventLoop::eloop` function
is called repeatedly. This runs the program.

There
are four general types of classes. The first is
Interface classes. Interfaces are physical buses that the code
interacts with. The second is Sensor classes. Sensors provide
code to interact with multiple interfaces to read data
from hardware. The third is Subsystem classes. Subsystems define
code that needs to run repeatedly and/or respond to
events and received packets. They can also talk to
interfaces and sensors. The fourth is Comms classes. Comms
classes provide code to read and write packets.
