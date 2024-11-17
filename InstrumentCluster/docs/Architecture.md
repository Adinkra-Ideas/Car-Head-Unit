## Wiring
The Diagram below illustrates our wiring setup for the PiRacer Instrument Cluster.

<img src="./imgs/DES01_Instrument_Cluster_wiring.png" width="70%" height="70%">

## High-level Data Flow Explanation

Below is a High-level explanation summarizing how we programmed the Outputs 
received from the LM393 Speed Sensor into our PiRacer's Instrument Cluster:

- It begins when the LM393 Speed Sensor sends out a HIGH Digital Output.
  The LM393 Speed Sensor sends out a HIGH Digital Output each time its Wheel
  rotates past a Hole. There are 20 Holes on its Wheel which means 20 HIGH
  Outputs equates One Full Wheel Rotation.
- The Arduino Nano receives these Digital Outputs, counts them until a
  certain Time has elapsed, before sending the Counts to the RPi via CAN
  Communication.
- Our C++ Qt Application running on the RPi retrieves this Counts using the
  Linux C/C++ SocketCAN API, uses a Custom Function to convert it into
  Distance, and feeds this Distance asynchronously into the instrument
  Cluster using QML.
- Meanwhile, a second thread runs concurrently on our RPi, using C/C++ to
  retrieve the Battery data from the INA219 Chip on our PiRacer through SPI
  communication. I compiled this Driver code used for abstracting the INA219
  Chip into a Dynamic Shared Library required during runtime. The benefit of
  this is that it creates a more organized codebase while also making future
  Driver updates easier and less complicated.


<br />
<br />
