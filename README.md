# DijakiOmare

Projekt za omarice v 5. nadstropju ERŠ-a. 

## Inštalacija
Za compiling kode, je potrebno importati priložen .zip v Arduino in dodati library SevSeg.
Potrebno je še dodati library Adafruit SSD1306. Ta doda tudi Wire in Adafruit GFX.

### Postavitev:
Skener kartic:\
Rdeča: 5V\
Črna: GND\
Digitalno:\
Zelena - 2\
Bela - 3

Display:\
GND: GND\
VCC: 5V ali 3.6V, je vseeno.\
Digitalno: SCL - 4\
           SDA - 6\
           RES - 5\
           DC - 7

Relay-i:\
Vsak rabi 5V napajalnik in 2 GND priklopa.\
Digitalno: Prvi štiri so od 10 - 14\
           Ostali so od: 22 - 53
