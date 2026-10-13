# Del 3 – Hints

## Opgave 3.1 – Tekst og tal

Tekst skal stå mellem anførselstegn. Tal skal stå uden anførselstegn.

```cpp
const char* WIFI_NAVN   = "NavnPåWiFi";   // Tekst
const int   SERVER_PORT = 1234;           // Tal
```

Store og små bogstaver skal være præcis, som de står på tavlen.

Hvis der står `Mangler oplysninger` i Serial Monitor, er der et eller flere felter, du ikke har udfyldt. Hvis der står `Forbinder til WiFi.......` i lang tid, er WiFi-navnet eller koden forkert.

---

## Opgave 3.2 – Kald en funktion

Koden indeholder en færdig funktion, der sender en besked til skærmen:

```cpp
sendTilServer("Den tekst, du vil sende");
```

At skrive navnet på en funktion efterfulgt af parenteser kaldes at **kalde** funktionen. Det, der står i parentesen, bliver sendt med ind i funktionen.

Du kan sætte tekst sammen med `+`:

```cpp
sendTilServer("Hej fra " + MIT_NAVN);
```

---

## Opgave 3.3 – Sammenlign tekst

Du kan tjekke, om to tekster er ens, med `==` (to lighedstegn):

```cpp
if (tekst == "NOGET") {
  // Kører kun, hvis tekst er præcis "NOGET"
}
```

Bemærk forskellen:

| Tegn | Betydning |
|---|---|
| `=` | Giv en variabel en værdi |
| `==` | Tjek om to ting er ens |

Inde i if-statementet skal du kalde funktionen `blink` med det antal gange, LED'en skal blinke.

---

## Ekstraopgave 3.4 – else if

Når du skal tjekke flere muligheder, kan du bruge `else if`:

```cpp
if (tekst == "A") {
  // ...
} else if (tekst == "B") {
  // ...
}
```

Til ON og OFF skal du bruge `digitalWrite` fra del 2. Til SOS kan du lave en for-løkke eller skrive `digitalWrite` og `delay` flere gange. Et kort blink kan være 200 millisekunder, et langt blink 600 millisekunder.

## Ekstraopgave 3.5 – IP-adresse som tekst

`WiFi.localIP()` giver din IP-adresse. Den kan laves om til tekst med `.toString()`:

```cpp
String ip = WiFi.localIP().toString();
```
