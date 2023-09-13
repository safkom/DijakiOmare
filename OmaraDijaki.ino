#include <Wiegand.h>

WIEGAND wg;

void setup() {
  Serial.begin(9600);
  wg.begin();
}

long kartice[36] = {0};

void loop() {
  long skeniranaKartica;
  
  if (wg.available()) {
    bool jeSkenirana = false;
    Serial.print("ID kartice = ");
    skeniranaKartica = wg.getCode();
    Serial.println(skeniranaKartica);

    for (int x = 0; x < 36; x++) {
      if (kartice[x] == skeniranaKartica) {
        kartice[x] = 0;
        jeSkenirana = true;
        break;
      }
    }

    if (!jeSkenirana) {
      for (int x = 0; x < 36; x++) {
        if (kartice[x] == 0) {
          kartice[x] = skeniranaKartica;
          jeSkenirana = false;
          break;
        }
      }
    }

    if (!jeSkenirana) {
      Serial.println("Uspešno skenirano.");
    }
    else if (jeSkenirana) {
      Serial.println("Kartica že obstaja v bazi. Brišem...");
    }

    Serial.println("Naslovi kartic: ");
    for (int x = 0; x < 36; x++) {
      Serial.print(kartice[x]);
      Serial.print(", ");
    }
    Serial.println();
    Serial.println();
  }

  //izpiši omarico na displayu
  
  //sproži relay
}
