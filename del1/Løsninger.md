# Del 1 – Løsninger

## Opgave 1.1

Der skal ikke skrives kode i opgave 1.1. Hvis det ikke virker, så se tabellen i [Hints.md](Hints.md).

## Opgave 1.2

```cpp
String MIT_NAVN = "Anna";
```

## Sådan virker programmet

Et Arduino-program har altid to dele:

```cpp
void setup() {
  // Kører én gang, når boardet starter
}

void loop() {
  // Kører igen og igen, så længe boardet har strøm
}
```

I `setup()` starter programmet forbindelsen til computeren (`Serial.begin(115200)`) og fortæller, at pin 15 skal styre LED'en (`pinMode(LED_PIN, OUTPUT)`).

I `loop()` tænder programmet LED'en (`HIGH`), venter 500 millisekunder (`delay(500)`), slukker LED'en (`LOW`) og venter igen. Derefter skriver det en besked til computeren med `Serial.println(...)`.
