# Vejledning til underviseren

## Forløb (2 timer)

| Tid | Indhold |
|---|---|
| 20 min | Fagligt oplæg: ESP32, IP-adresser, TCP og UDP |
| 15 min | Del 1: Installation og første upload. Kræver internet. |
| 20 min | Del 2: LED, for-løkke og if-statement, alene med egen ESP32 |
| 25 min | Del 3: Forbind til serveren. Navne på skærmen, BLINK til alle. |
| 25 min | Del 4: Beskeder mellem makkere |
| 15 min | Buffer. Del 5 og ekstraopgaverne er til de hurtigste. |

Delene bygger videre på hinanden. `blink()` og `knapErTrykket()` fra del 2 bliver brugt igen i del 3–5. `haandterBesked()` fra del 3 er det, der får makkerens LED til at blinke i del 4.

Forslag til fælles øjeblikke:

- **Del 3, opgave 3.1:** Navnene dukker op på skærmen, efterhånden som eleverne forbinder.
- **Del 3, opgave 3.3:** Tryk **BLINK** for alle, når de fleste har lavet opgaven.
- **Ekstraopgave 3.4 og 3.5:** Send `SOS` eller `HVEM` fra serveren.

## Netværk

- En router eller et hotspot på **2,4 GHz**. ESP32-C6 kan ikke bruge 5 GHz. Routeren behøver ikke internet.
- Giv server-computeren en fast IP-adresse, for eksempel via DHCP-reservation i routeren.
- Routeren skal kunne håndtere omkring 40 enheder, fordi der både er ESP32'ere og telefoner (del 5).
- Skriv på tavlen: WiFi-navn, kode, server-IP og port **5000**.

Værdierne i løsningsfilerne (`IoT-Workshop`, `12345678`, `192.168.1.100`, `5000`) er pladsholdere. Ret dem, hvis I bruger andre.

## Serveren

Kræver kun Python 3. Der skal ikke installeres nogen pakker.

```bash
cd server
python3 server.py
```

- ESP32'erne forbinder til port **5000** (TCP).
- Åbn **http://localhost:8080** på projektoren. Siden viser beskeder, forbundne enheder og serverens IP. Herfra kan I sende beskeder og kommandoerne `BLINK`, `ON` og `OFF` til én eller alle.
- På Windows: Tillad Python i firewallen på private netværk, når I bliver spurgt.
- Hver ESP32 kan sende højst 5 beskeder i sekundet. Det beskytter mod elever, der sender i en løkke uden pause.

### Protokol

Én tekstlinje pr. besked:

| Retning | Format | Betydning |
|---|---|---|
| ESP32 → server | første linje | Elevens navn |
| ESP32 → server | `tekst` | Vises på skærmen |
| ESP32 → server | `@navn\|tekst` | Sendes videre til eleven med det navn og vises på skærmen |
| server → ESP32 | `afsender\|tekst` | For eksempel `Server\|BLINK` eller `Anna\|PING` |

Eleverne ser ikke protokollen direkte. Den er pakket ind i funktionerne `sendTilServer()`, `sendTilPerson()` og `haandterBesked()` i skelettet.

## Hardware

DFRobot Beetle ESP32-C6: Den indbyggede LED sidder på **pin 15**, og BOOT-knappen på **pin 9**. I Arduino IDE vælges **ESP32C6 Dev Module** med **USB CDC On Boot: Enabled**.
