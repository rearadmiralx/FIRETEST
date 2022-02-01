#include <FirebaseESP32.h>  // Firebase Library server

// DHT
extern void Dht_Init();
extern void Dht_Loop();
extern float TemperatureValue();
extern float HumidityValue();

extern void RelayTest_Init();
extern void RelayTest_Loop();

extern void Lux_Init();
extern void Lux_Loop();
extern float LuxValue();

extern void Ph_Init();
extern float Ph_Loop();
extern float PhValue();


extern void Wifi_Init();
extern void Firebase_Init();
extern void Firebase_RelayInit();
extern void Firebase_SensorLoop();

extern void relayON(FirebaseJson relayJson);
extern void relayOFF(FirebaseJson relayJson);
extern void Firebase_RelayLoop();
extern void relayUpload(String path, String relayStatus);
extern void uploadSensorData(String status, String locationPath);
// extern void uploadSensorData(String status, FirebaseJson relay, String locationPath);


