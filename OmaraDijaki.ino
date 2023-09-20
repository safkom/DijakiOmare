#include <Wiegand.h>
#include "SevSeg.h"

WIEGAND wg;
SevSeg sevseg;

int relays[16]; // An array to store relay pins
bool relayActive[16]; // An array to track active relays
unsigned long relayActivationTime[16]; // An array to store activation time
unsigned long displayTurnOffTime = 0;
const unsigned long displayTurnOffDelay = 5000; // 5 seconds

void setup() {
  // Initialize relay pins
  for (int i = 0; i < 16; i++) {
    relays[i] = i + 34; // Set relay pins (assuming consecutive pins)
    pinMode(relays[i], OUTPUT);
    digitalWrite(relays[i], HIGH);
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
  sevseg.refreshDisplay(); // Initialize the display with a blank value
}

bool Skenirana = false;
long kartice[16] = {0}; // An array to store card IDs
int stKartic = 16;
int cardCount = 0; // Variable to track the number of stored card IDs

void loop() {
  long skeniranaKartica;
  if (wg.available()) {
    Skenirana = false;
    Serial.print("ID kartice = ");
    skeniranaKartica = wg.getCode();
    Serial.println(skeniranaKartica);

    OdstraniOmarico(skeniranaKartica);
    
    if (cardCount >= stKartic) {
      DisplayFull();
    }

    if(!Skenirana){
      DodajOmarico(skeniranaKartica);
    }

    PrintArray();
  }

  // Check if the array is full after the current scan
  if (millis() >= displayTurnOffTime) {
    sevseg.blank(); // Clear the display if not FULL and timeout
  }

  // Check and turn off relays based on the 5-second timer
  for (int x = 0; x < stKartic; x++) {
    if (relayActive[x] && millis() - relayActivationTime[x] >= 5000) {
      digitalWrite(relays[x], HIGH);
      relayActive[x] = false;
    }
  }

  sevseg.refreshDisplay();
}


void DodajOmarico(long skeniranaKartica){
    for (int x = 0; x < stKartic; x++) {
        if (kartice[x] == 0) {
          kartice[x] = skeniranaKartica;
          cardCount++;
          Serial.print("Dal kartico v omarico: ");
          Serial.println(x + 1);
          digitalWrite(relays[x], LOW);
          relayActivationTime[x] = millis();
          relayActive[x] = true;
          Skenirana = true;
          displayTurnOffTime = millis() + displayTurnOffDelay;
          sevseg.setNumber(x + 1);
          Serial.println("Uspešno skenirano. Vpisal v array.");
          break;
        }
      }
}

void OdstraniOmarico(long skeniranaKartica){
  for (int x = 0; x < stKartic; x++) {
      if (kartice[x] == skeniranaKartica) {
        Serial.print("Našel kartico za omarico: ");
        Serial.println(x + 1);
        digitalWrite(relays[x], LOW);
        relayActivationTime[x] = millis();
        relayActive[x] = true;
        Skenirana = true;
        displayTurnOffTime = millis() + displayTurnOffDelay;
        sevseg.setNumber(x + 1); // Update the display with the corresponding number
        kartice[x] = 0; // Reset the card in the array
        cardCount--; // Decrement the card count
        break;
      }
    }
}

void PrintArray(){
  Serial.print("Array vsebine: ");
    for (int x = 0; x < stKartic; x++) {
      Serial.print(kartice[x]);
      Serial.print(" ");
    }
    Serial.println();
    Serial.println(cardCount);
    Serial.println();
}

void DisplayFull(){
  sevseg.setChars("FULL");
  displayTurnOffTime = millis() + displayTurnOffDelay;
}
