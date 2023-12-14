#include <Wiegand.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h> // Dodajanje knjižnice za uporabo EEPROM

WIEGAND wg;

// Velikost zaslona
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Definicije pin-ov za OLED zaslon
#define OLED_CLK   4 // SCL
#define OLED_RESET 5 // RES
#define OLED_MOSI   6 // SDA
#define OLED_DC    7 // DC
#define OLED_CS    0 // Ni pomembno, samo mora biti določeno

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

// Definicije za releje in čas sprostitve
int relays[36];
bool relayActive[36];
unsigned long relayActivationTime[36];
unsigned long displayTurnOffTime = 0;
const unsigned long displayTurnOffDelay = 5000;

// Funkcija za branje stanja omaric iz EEPROM-a
void preberiStanjeOmaric() {
  for (int i = 0; i < 36; i++) {
    relayActive[i] = EEPROM.read(i) == 1;
    if (relayActive[i]) {
      digitalWrite(relays[i], LOW);
      relayActivationTime[i] = millis();
    }
  }
}

// Funkcija za pisanje stanja omaric v EEPROM
void zapisStanjaOmaric() {
  for (int i = 0; i < 36; i++) {
    EEPROM.write(i, relayActive[i] ? 1 : 0);
  }
  EEPROM.commit();
}

void setup() {
  // Določitev pin-ov za releje
  relays[1] = 53;
pinMode(relays[1], OUTPUT);
digitalWrite(relays[1], HIGH);
relayActive[1] = false;

relays[2] = 23;
pinMode(relays[2], OUTPUT);
digitalWrite(relays[2], HIGH);
relayActive[2] = false;

relays[3] = 51;
pinMode(relays[3], OUTPUT);
digitalWrite(relays[3], HIGH);
relayActive[3] = false;

relays[4] = 25;
pinMode(relays[4], OUTPUT);
digitalWrite(relays[4], HIGH);
relayActive[4] = false;

relays[5] = 49;
pinMode(relays[5], OUTPUT);
digitalWrite(relays[5], HIGH);
relayActive[5] = false;

relays[6] = 27;
pinMode(relays[6], OUTPUT);
digitalWrite(relays[6], HIGH);
relayActive[6] = false;

relays[7] = 47;
pinMode(relays[7], OUTPUT);
digitalWrite(relays[7], HIGH);
relayActive[7] = false;

relays[8] = 29;
pinMode(relays[8], OUTPUT);
digitalWrite(relays[8], HIGH);
relayActive[8] = false;

relays[9] = 45;
pinMode(relays[9], OUTPUT);
digitalWrite(relays[9], HIGH);
relayActive[9] = false;

relays[10] = 31;
pinMode(relays[10], OUTPUT);
digitalWrite(relays[10], HIGH);
relayActive[10] = false;

relays[11] = 43;
pinMode(relays[11], OUTPUT);
digitalWrite(relays[11], HIGH);
relayActive[11] = false;

relays[12] = 33;
pinMode(relays[12], OUTPUT);
digitalWrite(relays[12], HIGH);
relayActive[12] = false;

relays[13] = 41;
pinMode(relays[13], OUTPUT);
digitalWrite(relays[13], HIGH);
relayActive[13] = false;

relays[14] = 35;
pinMode(relays[14], OUTPUT);
digitalWrite(relays[14], HIGH);
relayActive[14] = false;

relays[15] = 39;
pinMode(relays[15], OUTPUT);
digitalWrite(relays[15], HIGH);
relayActive[15] = false;

relays[16] = 37;
pinMode(relays[16], OUTPUT);
digitalWrite(relays[16], HIGH);
relayActive[16] = false;

relays[17] = 22;
pinMode(relays[17], OUTPUT);
digitalWrite(relays[17], HIGH);
relayActive[17] = false;

relays[18] = 52;
pinMode(relays[18], OUTPUT);
digitalWrite(relays[18], HIGH);
relayActive[18] = false;

relays[19] = 24;
pinMode(relays[19], OUTPUT);
digitalWrite(relays[19], HIGH);
relayActive[19] = false;

relays[20] = 50;
pinMode(relays[20], OUTPUT);
digitalWrite(relays[20], HIGH);
relayActive[20] = false;

relays[21] = 26;
pinMode(relays[21], OUTPUT);
digitalWrite(relays[21], HIGH);
relayActive[21] = false;

relays[22] = 48;
pinMode(relays[22], OUTPUT);
digitalWrite(relays[22], HIGH);
relayActive[22] = false;

relays[23] = 28;
pinMode(relays[23], OUTPUT);
digitalWrite(relays[23], HIGH);
relayActive[23] = false;

relays[24] = 46;
pinMode(relays[24], OUTPUT);
digitalWrite(relays[24], HIGH);
relayActive[24] = false;

relays[25] = 30;
pinMode(relays[25], OUTPUT);
digitalWrite(relays[25], HIGH);
relayActive[25] = false;

relays[26] = 44;
pinMode(relays[26], OUTPUT);
digitalWrite(relays[26], HIGH);
relayActive[26] = false;

relays[27] = 32;
pinMode(relays[27], OUTPUT);
digitalWrite(relays[27], HIGH);
relayActive[27] = false;

relays[28] = 42;
pinMode(relays[28], OUTPUT);
digitalWrite(relays[28], HIGH);
relayActive[28] = false;

relays[29] = 34;
pinMode(relays[29], OUTPUT);
digitalWrite(relays[29], HIGH);
relayActive[29] = false;

relays[30] = 40;
pinMode(relays[30], OUTPUT);
digitalWrite(relays[30], HIGH);
relayActive[30] = false;

relays[31] = 46;
pinMode(relays[31], OUTPUT);
digitalWrite(relays[31], HIGH);
relayActive[31] = false;

relays[32] = 42;
pinMode(relays[32], OUTPUT);
digitalWrite(relays[32], HIGH);
relayActive[32] = false;

relays[33] = 44;
pinMode(relays[33], OUTPUT);
digitalWrite(relays[33], HIGH);
relayActive[33] = false;

relays[34] = 20;
pinMode(relays[34], OUTPUT);
digitalWrite(relays[34], HIGH);
relayActive[34] = false;

relays[35] = 19;
pinMode(relays[35], OUTPUT);
digitalWrite(relays[35], HIGH);
relayActive[35] = false;

relays[36] = 18;
pinMode(relays[36], OUTPUT);
digitalWrite(relays[36], HIGH);
relayActive[36] = false;

  relays[36] = 18;
  pinMode(relays[36], OUTPUT);
  digitalWrite(relays[36], HIGH);
  relayActive[36] = false;

  Serial.begin(9600);
  wg.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306: Napaka pri inicializaciji"));
    for (;;) {}
  }

  display.drawPixel(10, 10, SSD1306_WHITE);
  display.display();
  display.clearDisplay();

  // Branje stanja omaric iz EEPROM-a ob zagonu
  preberiStanjeOmaric();
}

bool Skenirana = false;
long kartice[36] = {0};
int stKartic = 36;
int cardCount = 0;

// Glavna zanka programa
void loop() {
  long skeniranaKartica;
  if (wg.available()) {
    Skenirana = false;
    skeniranaKartica = wg.getCode();

    OdstraniOmarico(skeniranaKartica);

    if (cardCount >= stKartic) {
      DisplayFull();
    }

    if (!Skenirana) {
      DodajOmarico(skeniranaKartica);
    }

    PrintArray();
  }

  if (millis() >= displayTurnOffTime) {
    display.clearDisplay();
  }

  for (int x = 0; x < stKartic; x++) {
    if (relayActive[x] && millis() - relayActivationTime[x] >= 5000) {
      digitalWrite(relays[x], HIGH);
      relayActive[x] = false;
    }
  }

  display.display();
  zapisStanjaOmaric();  // Posodobitev stanja omaric v EEPROM-u
}

// Dodajanje kartice v omarico
void DodajOmarico(long skeniranaKartica) {
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
      if ((x + 1) >= 10) {
        display.setTextSize(9);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(15, 0);
        display.println(x + 1);
        display.display();
      } else {
        display.setTextSize(8);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(40, 0);
        display.println(x + 1);
        display.display();
      }
      Serial.println("Uspešno skenirano. Vpisal v array.");
      break;
    }
  }
}

// Odstranjevanje kartice iz omarice
void OdstraniOmarico(long skeniranaKartica) {
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
      if ((x + 1) >= 10) {
        display.setTextSize(9);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(15, 0);
        display.println(x + 1);
        display.display();
      } else {
        display.setTextSize(8);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(40, 0);
        display.println(x + 1);
        display.display();
      }
      kartice[x] = 0;
      cardCount--;
      break;
    }
  }
}

// Izpis vsebine array-a
void PrintArray() {
  Serial.print("Array vsebine: ");
  for (int x = 0; x < stKartic; x++) {
    Serial.print(kartice[x]);
    Serial.print(" ");
  }
  Serial.println();
  Serial.println(cardCount);
  Serial.println();
}

// Izpis na zaslonu, če je array poln
void DisplayFull() {
  display.clearDisplay();
  display.setTextSize(5);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Vse omarice so zasedene!"));
  display.display();
  displayTurnOffTime = millis() + displayTurnOffDelay;
}
