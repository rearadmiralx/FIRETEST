#include <WiFi.h> // Wifi library

// Your WiFi credentials
#define WIFI_SSID "Redmitest"
#define WIFI_PASSWORD "123456780"

//User sa Bahay "GlobeAtHome_E1DB2"
//Pass sa Bahay "passwordnatin"

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