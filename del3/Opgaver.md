# Del 3 – Forbind til serveren

Vi har en server kørende på vores computer. En server er et program, der venter på, at andre forbinder til det. Alt, hvad I sender til serveren, bliver vist på skærmen i lokalet. Din ESP32 er en **klient**. Det betyder, at den er den, der forbinder til serveren.

```
Din ESP32 (klient)  --- WiFi ---  Vores server  ---  Skærmen i lokalet
```

Åbn filen `del3/del3_skelet/del3_skelet.ino`. Al koden til WiFi og forbindelsen er skrevet. Du skal kun udfylde de steder, hvor der står `OPGAVE`.

Hvis du ikke kan komme videre, så kig i [Hints.md](Hints.md). Den fulde løsning står i [Løsninger.md](Løsninger.md).

---

## Opgave 3.1 – Forbind til serveren

Øverst i koden er der fem linjer, som mangler oplysninger. Udfyld dem med de oplysninger, der står på tavlen:

| Navn i koden | Betydning |
|---|---|
| `WIFI_NAVN` | Navnet på workshoppens WiFi |
| `WIFI_KODE` | Koden til WiFi'et |
| `SERVER_IP` | Serverens IP-adresse, altså adressen på vores computer |
| `SERVER_PORT` | Portnummeret, som fortæller, hvilket program på computeren der skal modtage beskeden |
| `MIT_NAVN` | Dit navn, som det skal vises på skærmen |

Upload programmet, og åbn Serial Monitor.

**Resultat:** Dit navn bliver vist på skærmen i lokalet.

---

## Opgave 3.2 – Send en besked med knappen

Find `loop()`. Der er allerede et if-statement, som tjekker, om knappen bliver trykket. Skriv én linje inde i det, som sender en besked til skærmen.

**Resultat:** Din besked bliver vist på skærmen, hver gang du trykker på BOOT-knappen.

---

## Opgave 3.3 – Modtag kommandoer

Serveren kan også sende beskeder til jeres ESP32. Funktionen `haandterBesked` bliver kørt, hver gang der kommer en besked.

Skriv kode i `haandterBesked`, så LED'en blinker 5 gange, hvis beskeden er `BLINK`. Funktionen `blink()` fra del 2 er allerede med i koden.

**Resultat:** Når vi sender `BLINK` fra serveren, blinker LED'en på alle de ESP32'ere, der har lavet opgaven, på samme tid.

---

## Ekstraopgave 3.4 – Flere kommandoer (svær)

Udvid `haandterBesked`, så ESP32'en også forstår disse kommandoer:

| Kommando | Hvad skal ske |
|---|---|
| `ON` | LED'en tænder og bliver ved med at lyse |
| `OFF` | LED'en slukker |
| `SOS` | LED'en blinker SOS i morsekode: 3 korte, 3 lange, 3 korte |

## Ekstraopgave 3.5 – Svar på et spørgsmål (svær)

Lav det sådan, at hvis serveren sender `HVEM`, så svarer din ESP32 ved at sende sin IP-adresse til skærmen.
