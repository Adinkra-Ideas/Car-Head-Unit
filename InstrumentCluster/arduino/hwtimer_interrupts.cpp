#include <SPI.h>
#include <TimerOne.h> // Include the TimerOne library for hardware timer control

// #define Debug

#define CAN_2515
const int SPI_CS_PIN = 9; // Define the Chip Select (CS) pin for SPI communication

#ifdef CAN_2515
#include "mcp2515_can.h" // Include the MCP2515 CAN library
mcp2515_can CAN(SPI_CS_PIN); // Initialize the CAN object with the CS pin
#endif

// Variables for pulse counting and timing
volatile unsigned long pulses = 0; // Counter for pulses, marked as volatile since it's modified in an ISR
const unsigned long sampleTime = 500; // Sample time in milliseconds for the ISR
const int sensorPin = 3;           // Pin connected to the speed sensor

#ifdef Debug
const int resolution = 20;         // Number of pulses per revolution of the sensor
// Wheel measurements and speed calculations
const float wheelDiameterCm = 6.65; // Diameter of the wheel in centimeters
const float wheelCircumferenceCm = PI * wheelDiameterCm; // Circumference of the wheel in centimeters
const float wheelCircumferenceKm = wheelCircumferenceCm / 100000.0; // Circumference in kilometers
float speedKmh = 0.0; // Variable to store speed in km/h
float speedcms = 0.0;  // Variable to store speed in meters per second
#endif

void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud
  pinMode(sensorPin, INPUT); // Set the sensor pin as input
  attachInterrupt(digitalPinToInterrupt(sensorPin), countPulse, RISING); // Attach an interrupt to the sensor pin

  // Initialize the CAN bus at 500kbps and check if initialization is successful
  while (CAN_OK != CAN.begin(CAN_500KBPS)) {
    #ifdef Debug
    Serial.println("CAN init fail, retry...");
    #endif
    delay(100);
  }
  #ifdef Debug
  Serial.println("CAN init ok!");
  #endif

  // Initialize Timer1 with the sample time (converted to microseconds)
  Timer1.initialize(sampleTime * 1000);// the frame is sent every 500ms
  Timer1.attachInterrupt(sampleISR); // Attach the ISR for Timer1
}

// Interrupt Service Routine (ISR) for pulse counting
void countPulse() { 
  pulses++; // Increment the pulse count every time a pulse is detected
}

// ISR triggered by Timer1 to calculate and send speed data
void sampleISR() {
  noInterrupts(); // Temporarily disable interrupts
  unsigned long pulsesCount = pulses; // Copy the current pulse count
  pulses = 0; // Reset the pulse count
  interrupts(); // Re-enable interrupts

#ifdef Debug
  // Calculate RPM and speeds based on pulse count
  float rpm = (pulsesCount * 60.0) / (sampleTime / 1000.0) / (float)resolution;
  speedKmh = (rpm * wheelCircumferenceKm * 60); // Speed in km/h
  speedcms = (rpm * wheelCircumferenceCm / 60); // Speed in m/s

#endif

#ifdef Debug

  // Print the results to the Serial monitor in a single line
  Serial.println("Total pulses: " + String(pulsesCount));// + 
                //  " \t RPM: " + String(rpm) + 
                //  " \t Speed: " + String(speedKmh, 2) + " Km/h \t " + 
                //  String(speedcms, 2) + " cm/s");

#endif  


  // Prepare CAN data to send
  byte canData[2] = {
    // byte(rpm),
    // byte(speedKmh), byte(int(speedKmh * 100) % 100), // Split speedKmh into integer and decimal parts
    // byte(speedcms), byte(int(speedcms * 100) % 100),  // Split speedcms into integer and decimal parts
    highByte(pulsesCount), lowByte(pulsesCount), // Split pulse count into high and low bytes
//    0xff,0xff, 0xff, 0xff, 0xff, 0xff // Arbitrary byte for potential flag or identifier
  };

  // Send the data over the CAN bus and check for success
  byte sndStat = CAN.sendMsgBuf(0xBB, 0, 2, canData);
#ifdef Debug
  if (sndStat == CAN_OK) {
    Serial.println("CAN BUS sendMsgBuf ok!");
  } else {
    Serial.println("Error sending CAN message. Error code: " + String(sndStat));
  }
#endif
}

void loop() {
  // The loop can be empty as Timer1 handles the sampling and sending of data
}
