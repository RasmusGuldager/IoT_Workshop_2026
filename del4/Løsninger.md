# Del 4 – Løsninger

Det færdige program til opgave 4.1–4.3 ligger i `del4/del4_loesning/del4_loesning.ino`.

## Opgave 4.1

```cpp
String MAKKER = "Bo";
```

```cpp
  if (knapErTrykket()) {
    sendTilPerson(MAKKER, "BLINK");
  }
```

Din ESP32 sender beskeden til serveren sammen med navnet på modtageren. Serveren finder modtagerens forbindelse og sender beskeden videre. Når din makkers ESP32 modtager `BLINK`, kører den samme kode, som du skrev i opgave 3.3.

## Opgave 4.2

```cpp
  String tekst = laesFraSerialMonitor();
  if (tekst != "") {
    sendTilPerson(MAKKER, tekst);
  }
```

`!=` betyder "er ikke lig med". Koden sender altså kun noget, hvis der er skrevet noget.

## Opgave 4.3

```cpp
void haandterBesked(String afsender, String tekst) {
  if (tekst == "BLINK") {
    blink(5);
  }

  if (tekst == "PING") {
    sendTilPerson(afsender, "PONG");
  }
}
```

Svaret bliver sendt til `afsender` og ikke til `MAKKER`. Det betyder, at alle, der sender `PING` til dig, får et svar, også dem der ikke er din makker. Det er sådan, mange netværksprogrammer tjekker, om en anden enhed er tændt og kan svare.

## Ekstraopgave 4.4

```cpp
void haandterBesked(String afsender, String tekst) {
  if (tekst == "BLINK") {
    blink(5);
  } else if (tekst.startsWith("BLINK ")) {
    int antal = tekst.substring(6).toInt();
    blink(antal);
  }

  if (tekst == "PING") {
    sendTilPerson(afsender, "PONG");
  }
}
```

## Ekstraopgave 4.5

Øverst i filen:

```cpp
String bordet[] = {"Anna", "Bo", "Carl"};
int antalPaaBordet = 3;
```

I `loop()`:

```cpp
  if (knapErTrykket()) {
    for (int i = 0; i < antalPaaBordet; i++) {
      sendTilPerson(bordet[i], "BLINK");
    }
  }
```
