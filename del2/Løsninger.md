# Del 2 – Løsninger

Det færdige program til opgave 2.1–2.3 ligger i `del2/del2_loesning/del2_loesning.ino`.

## Opgave 2.1

```cpp
void blinkEnGang(int tid) {
  digitalWrite(LED_PIN, HIGH);
  delay(tid);

  digitalWrite(LED_PIN, LOW);

  delay(tid);
}
```

Uden den nye linje er LED'en tændt hele tiden, fordi den aldrig bliver slukket.

## Opgave 2.2

```cpp
void blink(int antal) {
  for (int i = 0; i < antal; i++) {
    blinkEnGang(200);
  }
}
```

Når `loop()` kalder `blink(3)`, får `antal` værdien 3. Løkken kører, mens `i` er 0, 1 og 2, altså 3 gange.

## Opgave 2.3

```cpp
void loop() {
  if (knapErTrykket()) {
    blink(3);
    delay(1000);
  }
}
```

`loop()` bliver kørt mange tusinde gange i sekundet. Hver gang tjekker if-statementet, om knappen er trykket. Det er kun, når svaret er sandt, at LED'en blinker.

## Ekstraopgave 2.4

Tilføj en variabel øverst i filen:

```cpp
int antalTryk = 0;
```

Og ret `loop()` til:

```cpp
void loop() {
  if (knapErTrykket()) {
    antalTryk = antalTryk + 1;
    Serial.println("Antal tryk: " + String(antalTryk));
    blink(antalTryk);
  }
}
```

Variablen skal stå uden for `loop()`. Hvis den stod inde i `loop()`, ville den blive sat til 0 igen, hver gang `loop()` startede forfra.
