# Del 5 – Løsninger

Det færdige program ligger i `del5/del5_loesning/del5_loesning.ino`.

## Opgave 5.1

```cpp
bool ledTaendt = false;

void skiftLed() {
  ledTaendt = !ledTaendt;
  if (ledTaendt) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  hjemmeside.send(200, "text/plain", "OK");
}
```

I `setup()`:

```cpp
  hjemmeside.on("/toggle", skiftLed);
```

Browseren og ESP32'en taler sammen med **HTTP**, som er den samme protokol, der bruges til alle hjemmesider. HTTP bruger selv TCP til at sende data.

## Opgave 5.2

```cpp
void sendHilsen() {
  sendTilServer("Hilsen fra hjemmesiden på " + MIT_NAVN + "s ESP32");
  hjemmeside.send(200, "text/plain", "OK");
}
```

I `setup()`:

```cpp
  hjemmeside.on("/hilsen", sendHilsen);
```

ESP32'en er nu både server (for telefonen) og klient (for vores server) på samme tid.

## Opgave 5.3

```cpp
void visStatus() {
  bool knapTrykket = (digitalRead(KNAP_PIN) == LOW);
  String json = "{\"led\": ";
  json += ledTaendt ? "true" : "false";
  json += ", \"knap\": ";
  json += knapTrykket ? "true" : "false";
  json += "}";
  hjemmeside.send(200, "application/json", json);
}
```

I `setup()`:

```cpp
  hjemmeside.on("/status", visStatus);
```

I HTML-koden, under de to `<p>`-linjer:

```html
<script>
  setInterval(async () => {
    const svar = await fetch('/status');
    const s = await svar.json();
    document.getElementById('led').textContent  = s.led  ? 'Tændt' : 'Slukket';
    document.getElementById('knap').textContent = s.knap ? 'Trykket' : 'Ikke trykket';
  }, 500);
</script>
```

Siden spørger ESP32'en om status to gange i sekundet. Det kaldes **polling**.

## Overvej

Ja. Alle på samme WiFi kan åbne din ESP32's IP-adresse og styre LED'en, fordi der hverken er kode eller login. Mange billige IoT-produkter har netop denne type sikkerhedshul.
