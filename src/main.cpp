#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Your WiFi credentials
#define WIFI_SSID "Pisonet"
#define WIFI_PASSWORD "nicopanget"

// Your Firebase Project Web API Key
#define API_KEY "AIzaSyApN_UInVP2mV0jKbsdAeRPUCXDYPZuCwU"
// Your Firebase Realtime database URL
#define DATABASE_URL "https://iot-aeroponics-default-rtdb.asia-southeast1.firebasedatabase.app"


// INSERT HERE THE RELAY PINS ACCORDINGLY
const int pinRelayPump = 26;

// Firebase Realtime Database Object
FirebaseData fbdo;
// Firebase Authentication Object
FirebaseAuth auth;
// Firebase configuration Object
FirebaseConfig config;

// Device Location config
String sensor = "sensor";
String relays = "relays";
// Firebase database path
String databasePath = ""; 
// Firebase Unique Identifier
String fuid = ""; 
// Stores the elapsed time from device start up
unsigned long elapsedMillis = 0; 
// The frequency of sensor updates to firebase, set to 10seconds
unsigned long update_interval = 10000; 
// Dummy counter to test initial firebase updates
int count = 0;

// Firebase json 
FirebaseJson relay_json;

String USER_EMAIL = "qcuph2021@gmail.com";
String USER_PASSWORD = "Password@123";

// Store device authentication status
bool isAuthenticated = false;


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

void Firebase_init() {
    // configure firebase API Key
    config.api_key = API_KEY;
    // configure firebase realtime database url
    config.database_url = DATABASE_URL;
    // Enable WiFi reconnection 
    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

    /* Assign the user sign in credentials */
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

    /* Assign the RTDB URL (required) */
    config.database_url = DATABASE_URL;

    /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback;

    Firebase.reconnectWiFi(true);
    Firebase.begin(&config, &auth);
    Serial.println("Getting User UID");
    while ((auth.token.uid) == "") {
      Serial.print('.');
      delay(1000);
    }
    fuid = auth.token.uid.c_str();
    Serial.print("User UID: ");
    Serial.print(fuid);
    isAuthenticated = true;
}



void relay_init(){
  relay_json.add("name", "Water Pump");
  relay_json.add("value", "OFF");

  // Print out initial temperature values
  String jsonStr;
  relay_json.toString(jsonStr, true);
  Serial.println(jsonStr);
}

String relayPump_ON(){
    relay_json.set("value", "ON");
    return "ON";
}
String relayPump_OFF(){
   relay_json.set("value", "OFF");
   return "OFF";
}

void uploadSensorData(String status) {
  if (millis() - elapsedMillis > update_interval && isAuthenticated && Firebase.ready())
    {
      elapsedMillis = millis();
      String relayPump = "relays/relayPump";
      
      if (Firebase.setJSON(fbdo, relayPump.c_str(), relay_json))
      {
          // Serial.println("PASSED");
          // Serial.println("PATH: " + fbdo.dataPath());
          // Serial.println("TYPE: " + fbdo.dataType());
          // Serial.println("ETag: " + fbdo.ETag());
          Serial.print("VALUE: ");
          printResult(fbdo); //see addons/RTDBHelper.h
          Serial.println("------------------------------------");
          Serial.println();
          
          if(status == "ON"){
              digitalWrite(pinRelayPump, HIGH);
              Serial.println("Pump is ON!");
          }
          else{
              digitalWrite(pinRelayPump, LOW);
              Serial.println("Pump is OFF!");
          }
          
      }
      else
      {
          Serial.println("FAILED");
          Serial.println("REASON: " + fbdo.errorReason());
          Serial.println("------------------------------------");
          Serial.println();
      } 
    }
}

void setup(){
   // Initialise serial communication for local diagnostics
    Serial.begin(115200);
    pinMode(pinRelayPump , OUTPUT);
    // Initialise Connection with location WiFi
    Wifi_Init();
    // Initialise firebase configuration and signup anonymously
   Firebase_init();
}

void loop(){
    uploadSensorData(relayPump_OFF());
    delay(10000);
    uploadSensorData(relayPump_ON());
    delay(10000);
}

