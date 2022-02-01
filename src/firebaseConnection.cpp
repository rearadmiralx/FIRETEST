#include <FirebaseESP32.h>  // Firebase Library server
#include "addons/TokenHelper.h" //Provide the token generation process info.
#include "addons/RTDBHelper.h" //Provide the RTDB payload printing info and other helper functions.
#include "header.h"

#define API_KEY "AIzaSyApN_UInVP2mV0jKbsdAeRPUCXDYPZuCwU" // Your Firebase Project Web API Key
#define DATABASE_URL "https://iot-aeroponics-default-rtdb.asia-southeast1.firebasedatabase.app" // Your Firebase Realtime database URL

FirebaseData fbdo; // Firebase Realtime Database Object
FirebaseAuth auth; // Firebase Authentication Object
FirebaseConfig config; // Firebase configuration Object
String fuid = ""; // Firebase Unique Identifier

String USER_EMAIL = "qcuph2021@gmail.com";
String USER_PASSWORD = "Password@123";
bool isAuthenticated = false;

FirebaseJson relayPump_json, relayFan_json, relayNutrientB_json, relayNutrientA_json, // Firebase json
             relayLight_json, relayphUp_json, relayPhDown_json;

FirebaseJson sensorHumidity_json, sensorLux_json, sensorPhLevel_json, sensorTds_json,
             sensorTemp_json, sensorWaterTemp_json;

//Pin Declaration
int pinRelayPump = 16;
int pinRelayLight = 33;
int pinRelayPhUp = 27;
int pinRelayPhDown = 14;
int pinRelayNutrientA = 26;
int pinRelayNutrientB = 17;
int pinRelayFan = 25;



// location path
String pathRelayPump = "relays/relayPump";
String pathRelayLight = "relays/relayLight";
String pathRelayNutrientA= "relays/relayNutrientA";
String pathRelayNutrientB = "relays/relayNutrientB";
String pathRelayPhUp = "relays/relayPhUp";
String pathRelayPhDown = "relays/relayPhDown";
String pathRelayFan = "relays/relayFan";

String pathSensor = "definedValue/sensor/";

//  Global variables
unsigned long elapsedMillis2 = 0; // Stores the elapsed time from device start ups
unsigned long update_interval2 = 10000; //
String pumpValue, lightValue, nutrientaValue, nutrientbValue,
       phUpValue, phDownValue, fanValue;

/**********************************************************************
 * 
 * ***    Methods for Relay Initialization
 * 
 **********************************************************************/ 
void Firebase_RelayInit(){

  relayPump_json.add("name", "Water Pump");
  if(pinRelayPump == HIGH){
    relayPump_json.add("value", "ON");
  }
  else{
    relayPump_json.add("value", "OFF");
  }

 // Print out initial temperature values
  String jsonStr;
  relayPump_json.toString(jsonStr, true);
  Serial.println(jsonStr);

}

/**********************************************************************
 * 
 * ***    Methods for Get Relay Status
 * 
 **********************************************************************/ 

void Relay_Status(){
  Serial.println("\n/**********************************************************************/\n");
  if (Firebase.getString(fbdo, pathRelayFan + "/value")) {
        fanValue = fbdo.stringData();
        Serial.println("fan is " + fanValue);
        fanValue == "ON" ? digitalWrite(pinRelayFan, HIGH): digitalWrite(pinRelayFan, LOW);
  }
  delay(1000);
  if (Firebase.getString(fbdo, pathRelayLight + "/value"))
  {
    lightValue = fbdo.stringData();
    Serial.println("lighRelay is " + lightValue);
    lightValue == "ON" ? digitalWrite(pinRelayLight, HIGH) : digitalWrite(pinRelayLight, LOW);
  }
  delay(1000);
  if (Firebase.getString(fbdo, pathRelayNutrientA + "/value")) {
        nutrientaValue = fbdo.stringData();
        Serial.println("nutrientA is " + nutrientaValue);
        nutrientaValue == "ON" ? digitalWrite(pinRelayNutrientA, HIGH) : digitalWrite(pinRelayNutrientA, LOW);
  }
  delay(1000);
  if (Firebase.getString(fbdo, pathRelayNutrientB + "/value")) {
        nutrientbValue = fbdo.stringData();
        Serial.println("nutrientB is " + nutrientbValue);
        nutrientbValue == "ON" ? digitalWrite(pinRelayNutrientB, HIGH) : digitalWrite(pinRelayNutrientB, LOW);
  }
  delay(1000);
  if (Firebase.getString(fbdo, pathRelayPhDown + "/value")) {
      phDownValue = fbdo.stringData();
      Serial.println("phDown is " + phDownValue);
      phDownValue == "ON" ? digitalWrite(pinRelayPhDown, HIGH) : digitalWrite(pinRelayPhDown, LOW);
  }
  delay(1000);
  if (Firebase.getString(fbdo, pathRelayPhUp + "/value")) {
        phUpValue = fbdo.stringData();
        Serial.println("ph UP is " + phUpValue);
        phUpValue == "ON" ? digitalWrite(pinRelayPhUp, HIGH) : digitalWrite(pinRelayPhUp, LOW);
  }

  // if (Firebase.getString(fbdo, pathRelayPump + "/value")) {
  //       pumpValue = fbdo.stringData();
  //       Serial.println("pumRelay is " + pumpValue + "\n");
  //       pumpValue == "ON" ? digitalWrite(pinRelayPump, HIGH) : digitalWrite(pinRelayPump, LOW);
  // }

}

/**********************************************************************
 * 
 * ***    Methods for Get Sensor Status
 * 
 **********************************************************************/ 


void Sensor_Status(FirebaseJson JsonVal, String path, float value){
  if (millis() - elapsedMillis2 > update_interval2 && isAuthenticated && Firebase.ready())
  {
    elapsedMillis2 = millis();

    Firebase.setFloat(fbdo, path, value);
  }
}

void SensorRollCallback(){
  // Sensor_Status(sensorLux_json, pathSensor+"lux/value", LuxValue());
  Sensor_Status(sensorPhLevel_json, pathSensor+"phLevel/value", PhValue());

}

// For Json Connection Only
void uploadSensorData(String status, String locationPath) {
  if (millis() - elapsedMillis2 > update_interval2 && isAuthenticated && Firebase.ready())
    {
      elapsedMillis2 = millis();

      if (Firebase.setJSON(fbdo, locationPath.c_str(), relayPump_json))
      {
          Serial.print("\nVALUE: ");
          Serial.print(fbdo.stringData());
          Serial.println("------------------------------------");
          Serial.println();
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

void Firebase_Init() {
    
    config.api_key = API_KEY;   // configure firebase API Key
    config.database_url = DATABASE_URL;     // configure firebase realtime database url
    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);  // Enable WiFi reconnection 

    /* Assign the user sign in credentials */
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

    config.database_url = DATABASE_URL;     //Assign the RTDB URL (required) 

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

    // Firebase_RelayInit();
}


/**********************************************************************
 * 
 * ***    Methods for Relay Initialization
 * 
 **********************************************************************/ 
void Firebase_RelayLoop(){
  Relay_Status();
}

void Firebase_SensorLoop(){
  SensorRollCallback();
}
