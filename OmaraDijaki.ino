#include <Wiegand.h>
#include "SevSeg.h"

WIEGAND wg;
SevSeg sevseg;

int relays[36]; // An array to store relay pins
bool relayActive[36]; // An array to track active relays
unsigned long relayActivationTime[36]; // An array to store activation time
unsigned long displayTurnOffTime = 0;
const unsigned long displayTurnOffDelay = 5000; // 5 seconds

void setup() {
  // Initialize relay pins
  for (int i = 0; i < 36; i++) {
    relays[i] = i + 6; // Set relay pins (assuming consecutive pins)
    pinMode(relays[i], OUTPUT);
    relayActive[i] = false; // Initialize relay states to off
  }

  Serial.begin(9600);
  wg.begin();

  byte numDigits = 4;
  byte digitPins[] = {22, 23, 24, 25};
  byte segmentPins[] = {26, 27, 28, 29, 30, 31, 32, 33};
  bool resistorsOnSegments = 0;
  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
}

long kartice[36] = {0}; // An array to store card IDs

void loop() {
  long skeniranaKartica;
  digitalWrite(relays[0], LOW); // Turn off the first relay
  sevseg.refreshDisplay();

  if (wg.available()) {
    bool jeSkenirana = false;
    Serial.print("ID kartice = ");
    skeniranaKartica = wg.getCode();
    Serial.println(skeniranaKartica);

    for (int x = 0; x < 36; x++) { // Iterate through all relays
      if (kartice[x] == skeniranaKartica) {
        Serial.print("Našel kartico za omarico: ");
        Serial.println(x + 1);
        sevseg.setNumber(x + 1);
        sevseg.refreshDisplay();
        digitalWrite(relays[x], HIGH); // Turn on the corresponding relay
        relayActivationTime[x] = millis(); // Record the activation time
        relayActive[x] = true; // Mark the relay as active
        kartice[x] = 0;
        jeSkenirana = true;
        displayTurnOffTime = millis() + displayTurnOffDelay;
        break;
      }
    }

    if (!jeSkenirana) {
      for (int x = 0; x < 36; x++) {
        if (kartice[x] == 0) {
          kartice[x] = skeniranaKartica;
          Serial.print("Dal kartico v omarico: ");
          Serial.println(x + 1);
          sevseg.setNumber(x + 1);
          sevseg.refreshDisplay();
          digitalWrite(relays[x], HIGH); // Turn on the corresponding relay
          relayActivationTime[x] = millis(); // Record the activation time
          relayActive[x] = true; // Mark the relay as active
          jeSkenirana = false;
          displayTurnOffTime = millis() + displayTurnOffDelay;
          break;
        }
      }
    }

    if (!jeSkenirana) {
      Serial.println("Uspešno skenirano.");
    } else if (jeSkenirana) {
      Serial.println("Kartica že obstaja v bazi. Brišem...");
    }

    Serial.println("Naslovi kartic: ");
    for (int x = 0; x < 36; x++) {
      Serial.print(kartice[x]);
      Serial.print(", ");
    }
    Serial.println();
  }

  // Check and turn off relays based on the 5-second timer
  for (int x = 0; x < 36; x++) {
    if (relayActive[x] && millis() - relayActivationTime[x] >= 5000) {
      digitalWrite(relays[x], LOW); // Turn off the relay when the 5-second interval has passed
      relayActive[x] = false; // Mark the relay as inactive
    }
  }

  if (millis() >= displayTurnOffTime) {
    sevseg.blank();
  }
}
