#include <WiFi.h> // Wifi library
#include "time.h"

// Your WiFi credentials
#define WIFI_SSID "guest"
#define WIFI_PASSWORD "1223334444!@"


const char* ntpServer = "ph.pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

//User sa HarveyBahay "GlobeAtHome_E1DB2"
//Pass sa Bahay "passwordnatin"

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

    //init and get the time
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    // printLocalTime();

    //disconnect WiFi as it's no longer needed
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
}


void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}
