#include <Wiegand.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
WIEGAND wg;

// Velikost zaslona
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Določitev pin-ov za zaslon:
#define OLED_CLK   4 // SCL
#define OLED_RESET 5 // RES
#define OLED_MOSI   6 // SDA
#define OLED_DC    7 // DC
#define OLED_CS    0 // ni važno, sam more bit
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

//Določitev relayov in čas sprostitve
int relays[36]; // 
bool relayActive[36];
unsigned long relayActivationTime[36];
unsigned long displayTurnOffTime = 0;
const unsigned long displayTurnOffDelay = 5000;

void setup() {
  
  // Določanje relayov digitalnim pinom
  for (int i = 0; i < 32; i++) {
    relays[i] = i + 22;
    pinMode(relays[i], OUTPUT);
    digitalWrite(relays[i], HIGH);
    relayActive[i] = false;
  }

  Serial.begin(9600);
  // Prižgemo čitalec za kartice
  wg.begin();

  //Pregledam če je display OK, in ga nastavim
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.drawPixel(10, 10, SSD1306_WHITE);
  display.display();
  display.clearDisplay();
}
//Dekleracije za kartice
bool Skenirana = false;
long kartice[36] = {0}; // An array to store card IDs
int stKartic = 36;
int cardCount = 0; // Variable to track the number of stored card IDs

void loop() {
  long skeniranaKartica;
  //Preverim, če je bila kartica skenirana
  if (wg.available()) {
    Skenirana = false;
    Serial.print("ID kartice = "); // Izpišem ID kartice
    skeniranaKartica = wg.getCode();
    Serial.println(skeniranaKartica);

    OdstraniOmarico(skeniranaKartica); //Najprej oddstranim kartico, če je že v arrayu
    
    if (cardCount >= stKartic) { // Če ni bila kartica v arrayu, in je array poln, to izpišem
      DisplayFull();
    }

    if(!Skenirana){ // Če array ni poln in kartica ni v arrayu, jo dodam
      DodajOmarico(skeniranaKartica);
    }

    PrintArray(); // Izpišem cel array
  }

  // Preverim če je že minilo 5 sec, da ugasnem zaslon
  if (millis() >= displayTurnOffTime) {
    display.clearDisplay(); // Clear the display if not FULL and timeout
  }

  // Preverim če je že minilo 5 sec, da ugasnem relay
  for (int x = 0; x < stKartic; x++) {
    if (relayActive[x] && millis() - relayActivationTime[x] >= 5000) {
      digitalWrite(relays[x], HIGH);
      relayActive[x] = false;
    }
  }

  display.display(); //Osvežim zaslon
}

// Funkcija za dodajanje kartice v array, in odklepanje omarice
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
// Funkcija za odstranitev kartice iz array-a, in odklepanje omarice
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
// Funckija za izpis array-a
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
// Funckija za izpis na zaslonu, če je array poln.
void DisplayFull(){
  display.clearDisplay();
  display.setTextSize(5);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Vse omarice so zasedene!"));
  display.display();
  displayTurnOffTime = millis() + displayTurnOffDelay;
}
