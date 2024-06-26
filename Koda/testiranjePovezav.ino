
// TA KODA JE SAMO ZA TESTIRANJE POVEZAV OD RELAY-A DO OMARIC




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
 
  relays[1] = 23;
  pinMode(relays[1], OUTPUT);
  digitalWrite(relays[1], LOW);
  relayActive[1] = false;

  relays[3] = 25;
  pinMode(relays[3], OUTPUT);
  digitalWrite(relays[3], LOW);
  relayActive[3] = false;

  relays[5] = 27;
  pinMode(relays[5], OUTPUT);
  digitalWrite(relays[5], LOW);
  relayActive[5] = false;

  relays[7] = 29;
  pinMode(relays[7], OUTPUT);
  digitalWrite(relays[7], LOW);
  relayActive[7] = false;

  relays[9] = 31;
  pinMode(relays[9], OUTPUT);
  digitalWrite(relays[9], LOW);
  relayActive[9] = false;

  relays[11] = 33;
  pinMode(relays[11], OUTPUT);
  digitalWrite(relays[11], LOW);
  relayActive[11] = false;

  relays[13] = 35;
  pinMode(relays[13], OUTPUT);
  digitalWrite(relays[13], LOW);
  relayActive[13] = false;

  relays[15] = 37;
  pinMode(relays[15], OUTPUT);
  digitalWrite(relays[15], LOW);
  relayActive[15] = false;

  relays[2] = 39;
  pinMode(relays[2], OUTPUT);
  digitalWrite(relays[2], LOW);
  relayActive[2] = false;

  relays[4] = 41;
  pinMode(relays[4], OUTPUT);
  digitalWrite(relays[4], LOW);
  relayActive[4] = false;

  relays[6] = 43;
  pinMode(relays[6], OUTPUT);
  digitalWrite(relays[6], LOW);
  relayActive[6] = false;

  relays[8] = 45;
  pinMode(relays[8], OUTPUT);
  digitalWrite(relays[8], LOW);
  relayActive[8] = false;

  relays[10] = 47;
  pinMode(relays[10], OUTPUT);
  digitalWrite(relays[10], LOW);
  relayActive[10] = false;

  relays[12] = 49;
  pinMode(relays[12], OUTPUT);
  digitalWrite(relays[12], LOW);
  relayActive[12] = false;

  relays[14] = 51;
  pinMode(relays[14], OUTPUT);
  digitalWrite(relays[14], LOW);
  relayActive[14] = false;

  relays[16] = 53;
  pinMode(relays[16], OUTPUT);
  digitalWrite(relays[16], LOW);
  relayActive[16] = false;

  relays[17] = 22;
  pinMode(relays[17], OUTPUT);
  digitalWrite(relays[17], LOW);
  relayActive[17] = false;

  relays[19] = 24;
  pinMode(relays[19], OUTPUT);
  digitalWrite(relays[19], LOW);
  relayActive[19] = false;

  relays[21] = 26;
  pinMode(relays[21], OUTPUT);
  digitalWrite(relays[21], LOW);
  relayActive[21] = false;

  relays[23] = 28;
  pinMode(relays[23], OUTPUT);
  digitalWrite(relays[23], LOW);
  relayActive[23] = false;

  relays[25] = 30;
  pinMode(relays[25], OUTPUT);
  digitalWrite(relays[25], LOW);
  relayActive[25] = false;

  relays[27] = 32;
  pinMode(relays[27], OUTPUT);
  digitalWrite(relays[27], LOW);
  relayActive[27] = false;

  relays[29] = 34;
  pinMode(relays[29], OUTPUT);
  digitalWrite(relays[29], LOW);
  relayActive[29] = false;

  relays[31] = 36;
  pinMode(relays[31], OUTPUT);
  digitalWrite(relays[31], LOW);
  relayActive[31] = false;

  relays[18] = 38;
  pinMode(relays[18], OUTPUT);
  digitalWrite(relays[18], LOW);
  relayActive[18] = false;

  relays[20] = 40;
  pinMode(relays[20], OUTPUT);
  digitalWrite(relays[20], LOW);
  relayActive[20] = false;

  relays[22] = 42;
  pinMode(relays[22], OUTPUT);
  digitalWrite(relays[22], LOW);
  relayActive[22] = false;

  relays[24] = 44;
  pinMode(relays[24], OUTPUT);
  digitalWrite(relays[24], LOW);
  relayActive[24] = false;

  relays[26] = 46;
  pinMode(relays[26], OUTPUT);
  digitalWrite(relays[26], LOW);
  relayActive[26] = false;

  relays[28] = 48;
  pinMode(relays[28], OUTPUT);
  digitalWrite(relays[28], LOW);
  relayActive[28] = false;

  relays[30] = 50;
  pinMode(relays[30], OUTPUT);
  digitalWrite(relays[30], LOW);
  relayActive[30] = false;

  relays[32] = 52;
  pinMode(relays[32], OUTPUT);
  digitalWrite(relays[32], LOW);
  relayActive[32] = false;

  relays[33] = 20;
  pinMode(relays[33], OUTPUT);
  digitalWrite(relays[33], LOW);
  relayActive[33] = false;

  relays[34] = 19;
  pinMode(relays[34], OUTPUT);
  digitalWrite(relays[34], LOW);
  relayActive[34] = false;

  relays[35] = 18;
  pinMode(relays[35], OUTPUT);
  digitalWrite(relays[35], LOW);
  relayActive[35] = false;

  relays[36] = 17;
  pinMode(relays[36], OUTPUT);
  digitalWrite(relays[36], LOW);
  relayActive[36] = false;


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

  Serial.print("Loading...");
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Pripravljam..."));
  display.display();
  delay(5000);
  Serial.print("Done!");
  Serial.println(" ");

  testRelays();
}
//Dekleracije za kartice
bool Skenirana = false;
long kartice[37] = {0}; // An array to store card IDs
int stKartic = 37;
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
    
    if (cardCount == 36) { // Če ni bila kartica v arrayu, in je array poln, to izpišem
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
  for (int x = 1; x < stKartic; x++) {
    if (relayActive[x] && millis() - relayActivationTime[x] >= 500) {
      digitalWrite(relays[x], LOW);
      relayActive[x] = false;
    }
  }

  display.display(); //Osvežim zaslon
}

// Funkcija za dodajanje kartice v array, in odklepanje omarice
void DodajOmarico(long skeniranaKartica){
    for (int x = 1; x < stKartic; x++) {
        if (kartice[x] == 0) {
          kartice[x] = skeniranaKartica;
          cardCount++;
          Serial.print("Dal kartico v omarico: ");
          Serial.println(x);
          digitalWrite(relays[x], HIGH);
          relayActivationTime[x] = millis();
          relayActive[x] = true;
          Skenirana = true;
          displayTurnOffTime = millis() + displayTurnOffDelay;
          display.clearDisplay();
          if(x  >= 10){
          display.setTextSize(6); // Prilagodite velikost besedila po potrebi
          display.setTextColor(SSD1306_WHITE);
          display.setCursor(15,0);
          display.println(x);
          display.display();
          }
          else{
          display.setTextSize(8); // Prilagodite velikost besedila po potrebi
          display.setTextColor(SSD1306_WHITE);
          display.setCursor(40,0);
          display.println(x);
          display.display();
          }
          
          Serial.println("Uspešno skenirano. Vpisal v array.");
          break;
        }
      }
}
// Funkcija za odstranitev kartice iz array-a, in odklepanje omarice
void OdstraniOmarico(long skeniranaKartica){
  for (int x = 1; x < stKartic; x++) {
    if (kartice[x] == skeniranaKartica) {
      Serial.print("Našel kartico za omarico: ");
      Serial.println(x);
      digitalWrite(relays[x], HIGH);
      relayActivationTime[x] = millis();
      relayActive[x] = true;

      Skenirana = true;
      displayTurnOffTime = millis() + displayTurnOffDelay;
      display.clearDisplay();
      if(x >= 10){
          display.setTextSize(6); // Prilagodite velikost besedila po potrebi
          display.setTextColor(SSD1306_WHITE);
          display.setCursor(18,2);
          display.println(x);
          display.display();
          }
          else{
          display.setTextSize(8); // Prilagodite velikost besedila po potrebi
          display.setTextColor(SSD1306_WHITE);
          display.setCursor(40,0);
          display.println(x);
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
    for (int x = 1; x < stKartic; x++) {
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
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Vse omarice so zasedene!"));
  display.display();
  Serial.println("Polno!");
  displayTurnOffTime = millis() + displayTurnOffDelay;
}

void testRelays() {
  for (int i = 1; i <= 36; i++) {
    digitalWrite(relays[i], LOW);
    delay(500); // Adjust delay as needed for testing
    digitalWrite(relays[i], HIGH);
    delay(500); // Adjust delay as needed for testing
    digitalWrite(relays[i], LOW);
    Serial.println("Testiral: " + i);
  }
  testRelays();
}

