# Del 5 – Ekstraopgaver: Din egen hjemmeside

Denne del er til dig, der er færdig med del 4 og gerne vil have en større udfordring. Her skal du selv skrive mere af koden.

I del 3 og 4 var din ESP32 en klient, der forbandt til vores server. Nu bliver din ESP32 **også selv en server**: Den laver en lille hjemmeside, som du kan åbne på din telefon. Samtidig er den stadig forbundet til vores server.

```
Din telefon  --- HTTP --->  Din ESP32  --- TCP --->  Vores server
```

Åbn filen `del5/del5_skelet/del5_skelet.ino`. Udfyld oplysningerne øverst ligesom i del 3. Hjemmesidens HTML-kode og knapper er skrevet, men knapperne gør ikke noget endnu.

Upload programmet. Find adressen i Serial Monitor (for eksempel `http://192.168.1.57`), og åbn den i browseren på din telefon. Telefonen skal være forbundet til workshoppens WiFi.

Hvis du ikke kan komme videre, så kig i [Hints.md](Hints.md). Den fulde løsning står i [Løsninger.md](Løsninger.md).

---

## Opgave 5.1 – Tænd og sluk fra telefonen

Når du trykker på knappen **Tænd / sluk LED**, beder browseren ESP32'en om adressen `/toggle`.

1. Lav en variabel, der husker, om LED'en er tændt.
2. Lav en funktion `skiftLed()`, som skifter LED'en mellem tændt og slukket og svarer browseren.
3. Tilføj adressen `/toggle` i `setup()`, så funktionen bliver kørt.

**Resultat:** Knappen på telefonen tænder og slukker LED'en.

---

## Opgave 5.2 – Send til skærmen fra telefonen

Knappen **Send hilsen til skærmen** beder om adressen `/hilsen`.

Lav en funktion `sendHilsen()`, som sender en besked til vores server, og tilføj adressen i `setup()`.

**Resultat:** Når du trykker på knappen på telefonen, bliver beskeden vist på skærmen i lokalet. Telefonen sender til ESP32'en, som sender videre til serveren.

---

## Opgave 5.3 – Live status

Hjemmesiden skal vise, om LED'en er tændt, og om BOOT-knappen bliver holdt nede, uden at man genindlæser siden.

1. Lav en funktion `visStatus()`, som svarer med status i JSON-format, for eksempel `{"led": true, "knap": false}`. Tilføj adressen `/status`.
2. Skriv JavaScript i HTML-koden, som henter `/status` to gange i sekundet og opdaterer teksten på siden.

**Resultat:** Når du holder BOOT-knappen nede, ændrer teksten på telefonen sig med det samme.

---

## Overvej

Kan andre i lokalet også åbne din hjemmeside og styre din LED? Hvad betyder det for sikkerheden i rigtige IoT-produkter?
