// Include your Arduino Library
#include<Arduino.h>
#include <FirebaseESP32.h> 
#include "header.h"

// INSERT HERE THE RELAY PINS ACCORDINGLY
// Initialization of your Sensors
// Global variables:

void setup(){
  // Initialise serial communication for local diagnostics
  Serial.begin(115200);
  Wifi_Init();
  Firebase_Init();
  Firebase_RelayInit();
  // Lux_Init();
  // Dht_Init();
  // RelayTest_Init();
}

void loop(){
  // Lux_Loop();
  // Dht_Loop();
  // RelayTest_Loop();
  Firebase_RelayLoop();
}