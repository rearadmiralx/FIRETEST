#include <Arduino.h>

const int pinRelayPump = 32;
const int pinRelayLight = 33;
const int pinRelayPhUp = 25;
const int pinRelayPhDown = 26;
const int pinRelayNutrientA = 27;
const int pinRelayNutrientB = 14;
const int pinRelayFan1 = 17;
const int pinRelayFan2 = 16;


void relayTest_Init(){
  pinMode(pinRelayPump , OUTPUT);
  pinMode(pinRelayLight , OUTPUT);
  pinMode(pinRelayPhUp , OUTPUT);
  pinMode(pinRelayPhDown , OUTPUT);
  pinMode(pinRelayNutrientA , OUTPUT);
  pinMode(pinRelayNutrientB, OUTPUT);
  pinMode(pinRelayFan1 , OUTPUT);
  pinMode(pinRelayFan2 , OUTPUT);
}

void RelayTest_Loop(){
  digitalWrite(pinRelayPump, HIGH);
  Serial.println("Pump On");
  delay(3000);
  digitalWrite(pinRelayPump, LOW);
  Serial.println("Pump Off");
  delay(3000);

  digitalWrite(pinRelayLight, HIGH);
  Serial.println("Light ON");
  delay(3000);
  digitalWrite(pinRelayLight, LOW);
  Serial.println("Light Off");
  delay(3000);

  digitalWrite(pinRelayPhUp, HIGH);
  Serial.println("PhUp On");
  delay(3000);
  digitalWrite(pinRelayPhUp, LOW);
  Serial.println("PhUp Off");
  delay(3000);

  digitalWrite(pinRelayPhDown, HIGH);
  Serial.println("PhDown On");
  delay(3000);
  digitalWrite(pinRelayPhDown, LOW);
  Serial.println("PhDown Off");
  delay(3000);

  digitalWrite(pinRelayNutrientA, HIGH);
  Serial.println("NutrientA On");
  delay(3000);
  digitalWrite(pinRelayNutrientA, LOW);
  Serial.println("NutrientA Off");
  delay(3000);

  digitalWrite(pinRelayNutrientB, HIGH);
  Serial.println("NutrientB On");
  delay(3000);
  digitalWrite(pinRelayNutrientB, LOW);
  Serial.println("NutrientB Off");
  delay(3000);

  digitalWrite(pinRelayFan1, HIGH);
  Serial.println("Fan On");
  delay(3000);
  digitalWrite(pinRelayFan1, LOW);
  Serial.println("Fan Off");
  delay(3000);

  digitalWrite(pinRelayFan2, HIGH);
  Serial.println("Fan2 On");
  delay(3000);
  digitalWrite(pinRelayFan2, LOW);
  Serial.println("Fan2 Off");
  delay(3000);

}
