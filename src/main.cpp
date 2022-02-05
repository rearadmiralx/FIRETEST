// Include your Arduino Library
#include<Arduino.h>
#include <FirebaseESP32.h> 
#include "header.h"

void setup(){
  // Initialise serial communication for local diagnostics
  Serial.begin(115200);
  Wifi_Init();
  // Firebase_Init();
  // Lux_Init();
  // Ph_Init();
  // Dht_Init();
  // RelayTest_Init();
}

void loop(){
  printLocalTime();
  // Ph_Loop();
  // Lux_Loop();
  // Dht_Loop();
  // // RelayTest_Loop();
  // Firebase_RelayLoop();
  // Firebase_SensorLoop();

}