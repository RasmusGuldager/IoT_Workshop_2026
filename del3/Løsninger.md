# Del 3 – Løsninger

Det færdige program til opgave 3.1–3.3 ligger i `del3/del3_loesning/del3_loesning.ino`.

## Opgave 3.1

Oplysningerne afhænger af tavlen. Det kan for eksempel se sådan ud:

```cpp
const char* WIFI_NAVN   = "IoT-Workshop";
const char* WIFI_KODE   = "12345678";
const char* SERVER_IP   = "192.168.1.100";
const int   SERVER_PORT = 5000;
String MIT_NAVN         = "Anna";
```

ESP32'en forbinder først til WiFi'et. Routeren giver den en IP-adresse, som bliver skrevet i Serial Monitor. Derefter forbinder ESP32'en til serveren. Den bruger serverens IP-adresse til at finde computeren og portnummeret til at finde det rigtige program på computeren. Forbindelsen bruger **TCP**, som sørger for, at alle beskeder kommer frem, og at de kommer i den rigtige rækkefølge.

## Opgave 3.2

```cpp
void loop() {
  holdForbindelse();

  if (knapErTrykket()) {
    sendTilServer("Hej fra " + MIT_NAVN);
  }
}
```

## Opgave 3.3

```cpp
void haandterBesked(String afsender, String tekst) {
  if (tekst == "BLINK") {
    blink(5);
  }
}
```

TCP-forbindelsen går begge veje. Serveren kan derfor sende beskeder tilbage til ESP32'en ad den samme forbindelse. Det er på samme måde, at smarte enheder i et hjem modtager kommandoer, for eksempel en lampe, der tænder, når man trykker i en app.

## Ekstraopgave 3.4

```cpp
void haandterBesked(String afsender, String tekst) {
  if (tekst == "BLINK") {
    blink(5);
  } else if (tekst == "ON") {
    digitalWrite(LED_PIN, HIGH);
  } else if (tekst == "OFF") {
    digitalWrite(LED_PIN, LOW);
  } else if (tekst == "SOS") {
    morseBlink(200);  // S: kort
    morseBlink(200);
    morseBlink(200);
    morseBlink(600);  // O: lang
    morseBlink(600);
    morseBlink(600);
    morseBlink(200);  // S: kort
    morseBlink(200);
    morseBlink(200);
  }
}

void morseBlink(int tid) {
  digitalWrite(LED_PIN, HIGH);
  delay(tid);
  digitalWrite(LED_PIN, LOW);
  delay(200);
}
```

## Ekstraopgave 3.5

Tilføj dette i `haandterBesked`:

```cpp
  if (tekst == "HVEM") {
    sendTilServer(MIT_NAVN + " har IP-adressen " + WiFi.localIP().toString());
  }
```
