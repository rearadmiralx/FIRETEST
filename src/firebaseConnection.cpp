#include <FirebaseESP32.h>  // Firebase Library server
#include "addons/TokenHelper.h" //Provide the token generation process info.
#include "addons/RTDBHelper.h" //Provide the RTDB payload printing info and other helper functions.

#define API_KEY "AIzaSyApN_UInVP2mV0jKbsdAeRPUCXDYPZuCwU" // Your Firebase Project Web API Key
#define DATABASE_URL "https://iot-aeroponics-default-rtdb.asia-southeast1.firebasedatabase.app" // Your Firebase Realtime database URL

FirebaseData fbdo; // Firebase Realtime Database Object
FirebaseAuth auth; // Firebase Authentication Object
FirebaseConfig config; // Firebase configuration Object
String fuid = ""; // Firebase Unique Identifier

String USER_EMAIL = "qcuph2021@gmail.com";
String USER_PASSWORD = "Password@123";
bool isAuthenticated = false;

FirebaseJson relayPump_json; // Firebase json 
FirebaseJson relayLight_json;
FirebaseJson relayphUp_json;
FirebaseJson relayPhDown_json;
FirebaseJson relayNutrientA_json;
FirebaseJson relayNutrientB_json;
FirebaseJson relayFan1_json;
FirebaseJson relayFan2_json;


//Pin Declaration
int pinRelayPump = 32;
int pinRelayLight = 33;
int pinRelayPhUp = 25;
int pinRelayPhDown = 26;
int pinRelayNutrientA = 27;
int pinRelayNutrientB = 14;
int pinRelayFan1 = 17;
int pinRelayFan2 = 16;

// location path
String PathrelayPump = "relays/relayPump/value";
String PathrelayLight = "relays/relayLight";
String PathrelayNutrientA= "relays/relayNutrientA";
String PathrelayNutrientB = "relays/relayNutrientB";
String PathrrelayPhUp = "relays/relayPhUp";
String PathrelayDown = "relays/relayDown";
String PathrelayFan1 = "relays/relayFan1";
String PathrelayFan2 = "relays/relayFan2";

//  Global variables
unsigned long elapsedMillis2 = 0; // Stores the elapsed time from device start ups
unsigned long update_interval2 = 10000; //



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

    Firebase_RelayInit();
}

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

String relayON(FirebaseJson relayJson){
    relayJson.set("value", "ON");
    return "ON";
}
String relayOFF(FirebaseJson relayJson){
   relayJson.set("value", "OFF");
   return "OFF";
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
          
          if(status == "ON"){
              // digitalWrite(pinRelayPump, HIGH);
              Serial.println("Pump is ON!");
          }
          else{
              // digitalWrite(pinRelayPump, LOW);
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

void relayUpload(String path, String relayStatus){
    Firebase.setString(fbdo, PathrelayPump, relayStatus);

     if(relayStatus == "ON"){
      Serial.println("PUmp oFF");
    }
    else{
      Serial.println("PUmp on");
    }
}

/**********************************************************************
 * 
 * ***    Methods for Relay Initialization
 * 
 **********************************************************************/ 
void Firebase_RelayLoop(){
 relayUpload(PathrelayPump, "OFF");
 delay(5000);
 relayUpload(PathrelayPump, "ON");
  delay(5000);
}

// void updateSensorReadings(){
//   Serial.println("------------------------------------");
//   Serial.println("Reading Sensor data ...");
//   temperature = dht.readTemperature();
//   humidity = dht.readHumidity();
//   // Check if any reads failed and exit early (to try again).
//   if (isnan(temperature) || isnan(humidity)) {
//   Serial.println(F("Failed to read from DHT sensor!"));
//   return;
//   }
//   Serial.printf("Temperature reading: %.2f \n", temperature);
//   Serial.printf("Humidity reading: %.2f \n", humidity);
//   temperature_json.set("value", temperature);
//   humidity_json.set("value", humidity);
// }