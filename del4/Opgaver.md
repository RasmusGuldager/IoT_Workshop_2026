# Del 4 – Tal med hinanden

I del 3 talte din ESP32 med serveren. Nu skal du bruge serveren til at sende beskeder til din makkers ESP32. Serveren sender beskeden videre til den rigtige person, ligesom et postkontor.

```
Din ESP32  --->  Serveren  --->  Din makkers ESP32
```

Åbn filen `del4/del4_skelet/del4_skelet.ino`. Den bygger videre på løsningen fra del 3.

Udfyld først de fem oplysninger øverst, ligesom i opgave 3.1. Du kan kopiere dem fra din kode i del 3.

Hvis du ikke kan komme videre, så kig i [Hints.md](Hints.md). Den fulde løsning står i [Løsninger.md](Løsninger.md).

---

## Opgave 4.1 – Få din makkers LED til at blinke

1. Skriv din makkers navn i `MAKKER`. Navnet skal staves præcis, som det står på skærmen.
2. Find `loop()`. Skriv én linje inde i if-statementet med knappen, som sender `BLINK` til din makker.

**Resultat:** Når du trykker på BOOT-knappen, blinker din makkers LED. Når din makker trykker, blinker din.

---

## Opgave 4.2 – Chat med din makker

Find `loop()`. Koden læser allerede det, du skriver i Serial Monitor, og gemmer det i variablen `tekst`. Skriv én linje, som sender `tekst` til din makker.

Skriv en besked i feltet øverst i Serial Monitor, og tryk Enter.

**Resultat:** Beskeden dukker op i din makkers Serial Monitor.

---

## Opgave 4.3 – Svar automatisk

Find `haandterBesked`. Lav det sådan, at hvis du modtager beskeden `PING`, så sender din ESP32 automatisk `PONG` tilbage til den, der sendte beskeden.

Afprøv det ved at bede din makker om at skrive `PING` i sin Serial Monitor.

**Resultat:** Din makker modtager `PONG` med det samme, uden at du gør noget.

---

## Ekstraopgave 4.4 – Bestem antallet af blink (svær)

Lav det sådan, at din makker kan sende for eksempel `BLINK 7`, og så blinker din LED 7 gange. Tallet skal kunne være et hvilket som helst tal.

## Ekstraopgave 4.5 – Send til flere på én gang (svær)

Lav en variabel med en liste af navne, for eksempel alle ved dit bord. Når du trykker på knappen, skal alle på listen få `BLINK`.
