# Del 4 – Hints

## Opgave 4.1 – sendTilPerson

Koden indeholder en færdig funktion, der sender en besked til én bestemt person:

```cpp
sendTilPerson("Navn", "Beskeden");
```

Den tager to ting i parentesen, adskilt af et komma: først hvem beskeden skal til, så hvad der står i den.

I stedet for at skrive navnet direkte kan du bruge variablen `MAKKER`. Variabler skal **ikke** stå i anførselstegn, kun tekst skal.

```cpp
sendTilPerson(MAKKER, "...");
```

Hvis du får beskeden `Kunne ikke finde nogen ved navn ...`, er navnet stavet forkert, eller din makker er ikke forbundet endnu.

---

## Opgave 4.2 – Variabler som besked

Det er den samme funktion som i 4.1. Forskellen er, at beskeden ikke er en fast tekst, men det, der står i variablen `tekst`.

---

## Opgave 4.3 – afsender

Funktionen `haandterBesked` får to ting med: `afsender` (hvem beskeden er fra) og `tekst` (hvad der står i beskeden).

Du skal bruge et if-statement, som tjekker `tekst`, ligesom `BLINK`-tjekket lige over. Inde i if-statementet skal du sende `PONG` til `afsender`.

---

## Ekstraopgave 4.4 – Del en tekst op

Disse funktioner kan bruges på tekst:

```cpp
tekst.startsWith("BLINK ")    // Er sand, hvis tekst starter med "BLINK "
tekst.substring(6)            // Teksten fra tegn nummer 6 og frem. "BLINK 7" giver "7"
tekst.substring(6).toInt()    // Laver teksten "7" om til tallet 7
```

Tegnene tælles fra 0, så `B` er tegn 0, og tallet starter ved tegn 6.

## Ekstraopgave 4.5 – Lister (arrays)

En liste af værdier kaldes et **array**:

```cpp
String bordet[] = {"Anna", "Bo", "Carl"};
int antalPaaBordet = 3;
```

Du kan hente et element med `bordet[0]`, `bordet[1]` og så videre. Brug en for-løkke fra del 2 til at gå igennem listen.
