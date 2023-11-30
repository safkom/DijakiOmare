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



PCB:
Datoteke za PCB za arduino so v Arduino - CNC mapi.
Tam so originalne datoteke za plato, rezkanje, luknje in rezanje obrobe.
Te se lahko kar direktno da na CNC mašino, oz. popravi če je potrebno.

3D printing:
Za 3D printing, se uporablja samo Ender 5 (tisti čist na levi), ker edini dela. My bad.
Za printanje samo rabiš it na računalnik, ki je vezan na C502 wifi, in greš na octopi.local

Geslo za wifi je: petonadstropje
Podatki za prijavo so:
Username: scv
Password: petonadstropje

Tam daš printat šablone za ključavnice, file je: CE5_prava.gcode
Samo stisneš gumb print in dela.

Ključavnice:
Vsaka rabi napajanje 12V, da dela. Sproži jih arduino, ko skeniraš kartico.
So montirane na desni strani zgoraj.


