# CAN Bus and Speed Sensor Project Documentation

## Overview

This documentation provides a detailed explanation of two approaches used in a project that involves reading speed sensor data and transmitting it over a CAN bus. The two approaches differ in how they handle timing and pulse counting:

1. **Software Interrupt (SW Interrupt) Approach**: This method uses a software-based approach, where interrupts are used to count sensor pulses, and the main loop periodically processes this data.

2. **Hardware Timer Interrupt (HW Timer Interrupt) Approach**: This method utilizes a hardware timer to trigger an interrupt at regular intervals, ensuring that data processing occurs at a consistent rate.

## Prerequisites

### Libraries

Both approaches require the following Arduino libraries:
- `SPI.h`: To handle SPI communication with the MCP2515 CAN controller.
- `mcp2515_can.h`: To interface with the MCP2515 CAN controller.
- `TimerOne.h`: (Only for the HW Timer Interrupt approach) To manage hardware timer operations.

### Hardware

- **MCP2515 CAN Controller**: For CAN bus communication.
- **Speed Sensor**: Connected to a digital input pin, used to measure rotational speed.

## Pin Configuration

- **SPI Chip Select Pin**: Pin 9
- **Sensor Pin**: Pin 3

## Approach 1: Software Interrupt (SW Interrupt) Approach

### Overview

In the SW Interrupt approach, an interrupt is attached to the sensor pin. Each time a rising edge is detected (indicating a pulse from the speed sensor), the interrupt service routine (ISR) `countPulse` increments the pulse count. The main loop runs periodically (every 1 second) to process the pulse count, calculate the speed, and send the data over the CAN bus.

### Code Explanation

#### Setup Function

- **Serial Communication**: Initializes the serial communication at 9600 baud.
- **Sensor Pin**: Configured as an input.
- **Interrupt Attachment**: The `attachInterrupt` function links the `countPulse` ISR to the sensor pin.
- **CAN Bus Initialization**: Attempts to initialize the CAN bus at 500 kbps, retrying until successful.

#### Interrupt Service Routine (ISR)

- **countPulse**: Increments the `pulses` variable each time a rising edge is detected on the sensor pin.

#### Main Loop

- **Time Tracking**: Tracks the time to ensure the main loop runs every 1 second (`sampleTime`).
- **Pulse Count Processing**: Temporarily disables interrupts to safely read and reset the pulse count.
- **RPM and Speed Calculation**: (Enabled if `Debug` is defined) Calculates the rotational speed in RPM and linear speed in km/h or cm/s.
- **CAN Data Transmission**: Prepares and sends the pulse count data over the CAN bus.

## Approach 2: Hardware Timer Interrupt (HW Timer Interrupt) Approach

### Overview

The HW Timer Interrupt approach uses a hardware timer to trigger an interrupt at regular intervals (every 500 ms). This ensures that pulse counts are processed at a consistent rate, independent of the main loop's timing. The timer ISR (`sampleISR`) calculates the speed and sends the data over the CAN bus.

### Code Explanation

#### Setup Function

- **Serial Communication**: Initializes the serial communication at 9600 baud.
- **Sensor Pin**: Configured as an input.
- **Interrupt Attachment**: The `attachInterrupt` function links the `countPulse` ISR to the sensor pin.
- **CAN Bus Initialization**: Attempts to initialize the CAN bus at 500 kbps, retrying until successful.
- **Timer1 Initialization**: Configures Timer1 to trigger an interrupt every 500 ms (`sampleTime`).

#### Interrupt Service Routine (ISR)

- **countPulse**: Increments the `pulses` variable each time a rising edge is detected on the sensor pin.
- **sampleISR**: Triggered by Timer1 every 500 ms, it processes the pulse count, calculates speed (if `Debug` is defined), and sends the data over the CAN bus.

#### Main Loop

- **Empty Loop**: The loop is empty because Timer1 handles all data processing and transmission.

## Summary

Both approaches are effective for counting pulses from a speed sensor and transmitting the data over a CAN bus. The SW Interrupt approach is simpler but may have timing inconsistencies due to the reliance on the main loop for timing. The HW Timer Interrupt approach ensures consistent timing by using a hardware timer, making it more robust for real-time applications. 

Choose the approach that best fits your project's requirements.
