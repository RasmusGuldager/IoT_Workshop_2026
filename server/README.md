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

## Start serveren og WiFi'et

Kræver Linux med NetworkManager og Python 3. Der skal ikke installeres nogen pakker.

```bash
cd server
python3 server.py
```

Serveren gør computeren til et 2,4 GHz-accesspoint, som ESP32'erne og telefonerne forbinder til. Der er ikke brug for internet. Navnet og koden står øverst i `server.py` (`WIFI_NAVN` og `WIFI_KODE`), og server-IP'en bliver normalt `10.42.0.1`.

- Computeren mister sin nuværende WiFi-forbindelse, mens serveren kører.
- Hotspottet bliver slukket igen, når serveren stoppes med Ctrl+C, eller når terminalen bliver lukket.
- Serveren skriver de fem værdier til opgave 3.1 i terminalen, og de står også øverst på projektorsiden. Skriv dem på tavlen.
- Mange indbyggede WiFi-kort kan kun have et begrænset antal enheder forbundet til et hotspot, nogle gange kun 8–16. Test det med fuldt hold før workshoppen.

Værdierne i løsningsfilerne (`IoT-Workshop`, `12345678`, `10.42.0.1`, `5000`) passer til standardindstillingerne.

## Serveren under workshoppen

- ESP32'erne forbinder til port **5000** (TCP).
- Åbn **http://localhost:8080** på projektoren. Siden viser WiFi-navn, kode, serverens IP og port, beskeder og forbundne enheder. Herfra kan I sende beskeder og kommandoerne `BLINK`, `ON` og `OFF` til én eller alle.
- Firewall på Windows: Tillad Python på private netværk, når I bliver spurgt.
- Firewall på Linux (ufw): Åbn port 5000 med `sudo ufw allow 5000/tcp`. Hotspottet skal også kunne dele IP-adresser ud: `sudo ufw allow in on <wifi-kort> to any port 67 proto udp` og `sudo ufw allow in on <wifi-kort> to any port 53`. Navnet på WiFi-kortet står i `nmcli device`.
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
