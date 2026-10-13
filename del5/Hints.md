# Del 5 – Hints

## Opgave 5.1 – Adresser og svar

En adresse på hjemmesiden kobles til en funktion i `setup()`:

```cpp
hjemmeside.on("/adresse", funktionensNavn);
```

Funktionen skal altid svare browseren, når den er færdig. `200` betyder, at alt gik godt:

```cpp
hjemmeside.send(200, "text/plain", "OK");
```

For at skifte mellem tændt og slukket skal du have en variabel af typen `bool`, som kan være `true` eller `false`. Den skal stå uden for funktionen, så den husker sin værdi. `!` betyder "det modsatte af":

```cpp
bool ledTaendt = false;

ledTaendt = !ledTaendt;   // true bliver til false, og false bliver til true
```

---

## Opgave 5.2 – Kombinér

Funktionen `sendTilServer` fra del 3 er med i koden. Den kan kaldes fra en hjemmesidefunktion på samme måde som fra `loop()`. Husk at svare browseren bagefter.

---

## Opgave 5.3 – JSON og JavaScript

**C++-delen:** Knappen kan læses med `digitalRead(KNAP_PIN)`. Den giver `LOW`, når knappen er trykket. JSON er bare tekst, som du kan bygge op med `+=`:

```cpp
String json = "{\"led\": ";
json += ledTaendt ? "true" : "false";
// ...
json += "}";
hjemmeside.send(200, "application/json", json);
```

`\"` er et anførselstegn inde i en tekst. `betingelse ? a : b` betyder: "hvis betingelsen er sand, så a, ellers b".

**JavaScript-delen:** Skriv det i et `<script>`-tag i HTML-koden:

```javascript
setInterval(async () => {
  const svar = await fetch('/status');      // Spørg ESP32'en
  const s = await svar.json();              // Lav svaret om til et objekt
  // s.led og s.knap er nu true eller false
  document.getElementById('led').textContent = 'noget tekst';
}, 500);                                    // Gentag hvert 500. millisekund
```
