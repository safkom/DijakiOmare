#include <Wiegand.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
WIEGAND wg;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   5
#define OLED_CLK   4
#define OLED_DC    7
#define OLED_CS    12
#define OLED_RESET 6
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

int relays[36]; // An array to store relay pins
bool relayActive[36]; // An array to track active relays
unsigned long relayActivationTime[36]; // An array to store activation time
unsigned long displayTurnOffTime = 0;
const unsigned long displayTurnOffDelay = 5000; // 5 seconds

void setup() {
  
  // Initialize relay pins
  for (int i = 0; i < 32; i++) {
    relays[i] = i + 22; // Set relay pins (assuming consecutive pins)
    pinMode(relays[i], OUTPUT);
    digitalWrite(relays[i], HIGH);
    relayActive[i] = false; // Initialize relay states to off
  }

  Serial.begin(9600);
  wg.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.drawPixel(10, 10, SSD1306_WHITE);
  display.display();
  display.clearDisplay();
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
    display.clearDisplay(); // Clear the display if not FULL and timeout
  }

  // Check and turn off relays based on the 5-second timer
  for (int x = 0; x < stKartic; x++) {
    if (relayActive[x] && millis() - relayActivationTime[x] >= 5000) {
      digitalWrite(relays[x], HIGH);
      relayActive[x] = false;
    }
  }

  display.display();
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
          display.clearDisplay();
          if((x + 1)  >= 10){
          display.setTextSize(9); // Prilagodite velikost besedila po potrebi
          display.setTextColor(SSD1306_WHITE);
          display.setCursor(15,0);
          display.println(x + 1);
          display.display();
          }
          else{
          display.setTextSize(8); // Prilagodite velikost besedila po potrebi
          display.setTextColor(SSD1306_WHITE);
          display.setCursor(40,0);
          display.println(x + 1);
          display.display();
          }
          
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
      display.clearDisplay();
      if((x + 1)  >= 10){
          display.setTextSize(9); // Prilagodite velikost besedila po potrebi
          display.setTextColor(SSD1306_WHITE);
          display.setCursor(15,0);
          display.println(x + 1);
          display.display();
          }
          else{
          display.setTextSize(8); // Prilagodite velikost besedila po potrebi
          display.setTextColor(SSD1306_WHITE);
          display.setCursor(40,0);
          display.println(x + 1);
          display.display();
          }
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
  display.clearDisplay();
  display.setTextSize(5);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Vse omarice so zasedene!"));
  display.display();
  displayTurnOffTime = millis() + displayTurnOffDelay;
}
