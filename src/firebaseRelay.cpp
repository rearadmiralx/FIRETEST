// #include <FirebaseESP32.h>  // Firebase Library server

// FirebaseData fbdo2; // Firebase Realtime Database Object
// FirebaseAuth auth2; // Firebase Authentication Object
// FirebaseConfig config2; // Firebase configuration Object
// // Device Location config
// // String sensor = "sensor";
// // String relays = "relays";

// String databasePath2 = "";  // Firebase database path
// FirebaseJson relayPump_json; // Firebase json 
// FirebaseJson relayLight_json;
// FirebaseJson relayphUp_json;
// FirebaseJson relayPhDown_json;
// FirebaseJson relayNutrientA_json;
// FirebaseJson relayNutrientB_json;
// FirebaseJson relayFan1_json;
// FirebaseJson relayFan2_json;
// unsigned long elapsedMillis2 = 0; // Stores the elapsed time from device start ups
// unsigned long update_interval2 = 10000; // The frequency of sensor updates to firebase, set to 10second
// int count2 = 0; // Dummy counter to test initial firebase updates


// //Pin Declaration
// int pinRelayPump = 32;
// int pinRelayLight = 33;
// int pinRelayPhUp = 25;
// int pinRelayPhDown = 26;
// int pinRelayNutrientA = 27;
// int pinRelayNutrientB = 14;
// int pinRelayFan1 = 17;
// int pinRelayFan2 = 16;

// // location path
// String PathrelayPump = "relays/relayPump";
// String PathrelayLight = "relays/relayLight";
// String PathrelayNutrientA= "relays/relayNutrientA";
// String PathrelayNutrientB = "relays/relayNutrientB";
// String PathrrelayPhUp = "relays/relayPhUp";
// String PathrelayDown = "relays/relayDown";
// String PathrelayFan1 = "relays/relayFan1";
// String PathrelayFan2 = "relays/relayFan2";

// String data2 = Firebase.getString(fbdo2, "relays/relayPump/value") ? fbdo2.stringData() : fbdo2.errorReason().c_str();

// void Firebase_RelayInit(){
// //   relayPump_json.add("name", "Water Pump");
// //   relayPump_json.add("value", "OFF");

// //   // Print out initial temperature values
// //   String jsonStr;
// //   relayPump_json.toString(jsonStr, true);
// //   Serial.println(jsonStr);

// Serial.print("Initial value of Fan is \n");
// Serial.println(data2);
// }

// String relayON(FirebaseJson relayJson){
//     relayJson.set("value", "ON");
//     return "ON";
// }
// String relayOFF(FirebaseJson relayJson){
//    relayJson.set("value", "OFF");
//    return "OFF";
// }

// // For Json Connection Only
// void uploadSensorData(String status, FirebaseJson relay, String locationPath) {
//   if (millis() - elapsedMillis2 > update_interval2 && Firebase.ready())
//     {
//       elapsedMillis2 = millis();

//       if (Firebase.setJSON(fbdo2, locationPath.c_str(), relay))
//       {
//           Serial.print("\nVALUE: ");
//           Serial.print(fbdo2.stringData());
//           Serial.println("------------------------------------");
//           Serial.println();
          
//           if(status == "ON"){
//               digitalWrite(pinRelayPump, HIGH);
//               Serial.println("Pump is ON!");
//           }
//           else{
//               digitalWrite(pinRelayPump, LOW);
//               Serial.println("Pump is OFF!");
//           }
//       }
//       else
//       {
//           Serial.println("FAILED");
//           Serial.println("REASON: " + fbdo2.errorReason());
//           Serial.println("------------------------------------");
//           Serial.println();
//       } 
//     }
// }

// void relayUpload(String path, String relayStatus){
//     Firebase.setString(fbdo2, PathrelayPump + "/value", relayStatus);
// }

// void Firebase_RelayLoop(){
//     relayUpload(PathrelayPump, data2);
//     delay(3000);

// }