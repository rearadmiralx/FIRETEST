#include <WiFi.h> // Wifi library

// Your WiFi credentials
#define WIFI_SSID "GlobeAtHome_E1DB2"
#define WIFI_PASSWORD "passwordnatin"

//User sa Bahay "GlobeAtHome_E1DB2"
//Pass sa Bahay "5DFF74E1"

//User kila Jim "Pisonet"
//Pass kila Jim "nicopanget"

void Wifi_Init() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");

    while (WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(300);

    }

    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
}