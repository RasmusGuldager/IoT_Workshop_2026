# Del 1 – Installation og dit første program

I denne del installerer du det program, som bruges til at skrive kode til ESP32'en. Bagefter overfører du et færdigt program til boardet.

Bruger du hints og løsninger, ligger de i [Hints.md](Hints.md) og [Løsninger.md](Løsninger.md).

> **Vigtigt:** Del 1 kræver internet. Gør den færdig, før du skifter til workshoppens WiFi.

---

## Opgave 1.1 – Installér Arduino IDE og overfør et program

**Installér programmet**

1. Gå ind på <https://www.arduino.cc/en/software>, og hent **Arduino IDE** til din computer (Windows, Mac eller Linux).
2. Installér det, ligesom du plejer at installere programmer, og åbn det.

**Installér understøttelse af ESP32**

3. Klik på ikonet, der ligner et lille board, i venstre side af vinduet. Det er **Boards Manager**.
4. Skriv `esp32` i søgefeltet.
5. Find **esp32 by Espressif Systems**, og klik på **Install**. Det kan tage et par minutter.

**Åbn programmet til del 1**

6. Vælg **File → Open** i menuen.
7. Find mappen, du har downloadet, og åbn filen `del1/del1_kode/del1_kode.ino`.

**Tilslut ESP32'en**

8. Sæt ESP32'en i computeren med USB-kablet.
9. Vælg **Tools → Board → esp32 → ESP32C6 Dev Module** i menuen.
10. Vælg **Tools → Port**, og vælg den port, der dukkede op, da du satte boardet i.
11. Vælg **Tools → USB CDC On Boot → Enabled**. Uden denne indstilling kan du ikke se, hvad boardet skriver.

**Overfør programmet**

12. Klik på knappen med en pil (**Upload**) øverst til venstre. Vent, til der står *Done uploading* nederst.
13. Klik på forstørrelsesglasset øverst til højre for at åbne **Serial Monitor**.
14. Vælg **115200 baud** i menuen nederst i Serial Monitor.

**Resultat:** LED'en på boardet blinker én gang i sekundet, og i Serial Monitor står der `Hej Skriv dit navn her. Din ESP32 har kørt i ... sekunder.`

---

## Opgave 1.2 – Skriv dit navn

Find denne linje øverst i koden:

```cpp
String MIT_NAVN = "Skriv dit navn her";
```

Skift teksten mellem anførselstegnene ud med dit eget navn, og overfør programmet igen (opgave 1.1, trin 12).

**Resultat:** I Serial Monitor står der nu `Hej <dit navn>. ...`.
