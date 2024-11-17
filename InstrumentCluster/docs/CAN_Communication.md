
# CAN Communication
This section describes the CAN Bus Setup we used for our PiRacer Instrument Cluster. 

## Materials
The following materials are used for this section. The Speed Sensor (LM393) is connected with Arduino Nano and the Arduino Nano is connected with MCP2515 CAN Module. The CAN BUS is established between the MCP2515 and the 2CH CAN BUS FD HAT. 
The 2CH CAN BUS FD HAT is connected with Raspberry Pi 4. 
The drivetrain of the PiRacer is connected via I2C with the Raspberry Pi 4.

| PiRacer | Raspberry Pi 4 | 2CH CAN-BUS FD HAT | MCP2515 | Arduino Nano | SpeedSensor |
|:-------:|:-------:|:-------------------:|:-------:|:-----------:|:------------------:|
|<img src="./imgs/piracer.jpg" alt="piracer" >|<img src="./imgs/raspberry-pi-4-modell-b.jpg" alt="RPi" width="70%" height="70%">|<img src="./imgs/2ch-can-fd-hat.jpg" alt="2ch CAN BUS FD HAT" width="70%" height="70%">|<img src="./imgs/MCP2515.png" alt="MCP2515" width="70%" height="70%">|<img src="./imgs/Arduino_Nano.jpg" alt="Arduino Nano" width="70%" height="50%">|<img src="./imgs/speedsensor.png" alt="speed sensor" width="70%" height="70%">|

## Wiring
The Diagram below illustrates our wiring setup for the PiRacer Instrument Cluster.

<img src="./imgs/DES01_Instrument_Cluster_wiring.png" width="70%" height="70%">


## Set Up 
Raspberry Pi with Debian(Bullseye) OS and 2CH-CAN-FD-HAT.<br>
[How to set up 2CH-CAN-FD-HAT](https://www.waveshare.com/wiki/Template:2-CH_CAN_FD_HAT_User_Manual#Working_with_Raspberry_Pi)
> **Note** Use Dual SPI Mode. Sometimes can0 and can01 is swapped, so please keep this in mind. If they are swapped, you have to rename can0 can1.

## Code Example for testing
### Transmitter Code Example (Arduino Nano)
> **Note**: The Arduino model might cause this not to work for you if you dont get the Oscillation and CS Pin right ;)

```ino
#include <SPI.h> 
#include "mcp2515_can.h"

#define MSG_ID 0x21

const uint16_t periodMS = 1000;

const int SPI_CS_PIN = 10;
mcp2515_can CAN(SPI_CS_PIN);

unsigned long myMillis;
unsigned long lastTriggerMillis;

const uint8_t pinForSpdSnsr = 3;
volatile byte counter = 1;

void setup() {
  Serial.begin(9600);
  while(!Serial){};
  while (CAN_OK != CAN.begin(CAN_500KBPS, MCP_8MHz)) {
      Serial.println("CAN init fail, retry...");
      delay(100);
  }
  Serial.println("CAN init ok!");

  pinMode(pinForSpdSnsr, INPUT); 
  attachInterrupt(digitalPinToInterrupt(pinForSpdSnsr), onHIGH, RISING);
  lastTriggerMillis = millis();
}

void loop() {
  myMillis = millis();
  if ((myMillis - lastTriggerMillis) >= periodMS) {
    sendFullRotationsCount();
    lastTriggerMillis = myMillis;
  }
}

void onHIGH() {
  ++counter;
}

void sendFullRotationsCount() {
  Serial.println(counter);
  CAN.sendMsgBuf(
    MSG_ID, 
    0,
    1,
    &counter
  );
  
  counter = 0;
}

```

