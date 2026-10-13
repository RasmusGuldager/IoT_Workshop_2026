# Del 2 – Hints

## Opgave 2.1 – digitalWrite

`digitalWrite` bestemmer, om der skal være strøm på en pin eller ej.

```cpp
digitalWrite(LED_PIN, HIGH);   // Strøm på: LED'en tænder
digitalWrite(LED_PIN, LOW);    // Strøm af: LED'en slukker
```

Kig på linjen lige over den plads, hvor du skal skrive. Den gør det modsatte af det, du skal.

---

## Opgave 2.2 – for-løkke

En for-løkke gentager noget et bestemt antal gange. Den ser sådan ud:

```cpp
for (int i = 0; i < 5; i++) {
  // Koden her bliver kørt 5 gange
}
```

Den består af tre dele adskilt af semikolon:

| Del | Betydning |
|---|---|
| `int i = 0` | Lav en tæller, der hedder `i`, og start på 0 |
| `i < 5` | Bliv ved, så længe `i` er mindre end 5 |
| `i++` | Læg 1 til `i` efter hver gang |

Al koden mellem `{` og `}` bliver gentaget.

I opgaven skal løkken ikke køre 5 gange, men `antal` gange.

---

## Opgave 2.3 – if-statement

Et if-statement kører kun noget kode, **hvis** noget er sandt. Det ser sådan ud:

```cpp
if (betingelse) {
  // Denne kode bliver kun kørt, hvis betingelsen er sand
}
```

Funktionen `knapErTrykket()` giver svaret *sand* (`true`), når knappen bliver trykket, og *falsk* (`false`), når den ikke gør. Den kan derfor bruges direkte som betingelse.

Husk, at begge linjer i `loop()` skal stå mellem `{` og `}`.

---

## Ekstraopgave 2.4 – Variabler

En variabel er et navn, som kan huske en værdi. Hvis variablen skal huske sin værdi mellem hver gang `loop()` kører, skal den laves øverst i filen, uden for alle funktioner:

```cpp
int antalTryk = 0;
```

Du kan lægge 1 til med:

```cpp
antalTryk = antalTryk + 1;
```

Du kan bruge variablen der, hvor der før stod et tal, fx `blink(antalTryk);`.
