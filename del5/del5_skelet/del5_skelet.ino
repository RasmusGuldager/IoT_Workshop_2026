// Del 5 - Ekstraopgaver: Din egen hjemmeside
//
// I denne del skal du selv skrive mere af koden. Se Opgaver.md.

#include <WiFi.h>
#include <WebServer.h>

WebServer hjemmeside(80);  // Hjemmesiden kører på port 80 (standard for http)

// Udfyld oplysningerne fra tavlen (de samme som i del 3).
const char* WIFI_NAVN   = "";
const char* WIFI_KODE   = "";
const char* SERVER_IP   = "";
const int   SERVER_PORT = 0;
String MIT_NAVN         = "";

const int LED_PIN = 15;   // Den indbyggede LED
const int KNAP_PIN = 9;   // BOOT-knappen på boardet

// HTML-koden til hjemmesiden. Alt mellem R"html( og )html" er almindelig tekst.
const char SIDE[] = R"html(
<!doctype html>
<html>
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Min ESP32</title>
  <style>
    body { font-family: sans-serif; text-align: center; padding: 40px; }
    button { font-size: 24px; padding: 16px 32px; margin: 10px; border-radius: 8px; }
    p { font-size: 22px; }
  </style>
</head>
<body>
  <h1>Min ESP32</h1>
  <button onclick="fetch('/toggle')">Tænd / sluk LED</button>
  <button onclick="fetch('/hilsen')">Send hilsen til skærmen</button>

  <!-- OPGAVE 5.3: Vis status for LED og BOOT-knap her, og opdatér den med JavaScript -->
  <p>LED: <b id="led">?</b></p>
  <p>BOOT-knap: <b id="knap">?</b></p>

</body>
</html>
)html";


// ==========================================================================
// Din kode
// ==========================================================================

void visSide() {
  hjemmeside.send(200, "text/html; charset=utf-8", SIDE);
}

// OPGAVE 5.1: Lav en funktion skiftLed(), som tænder LED'en, hvis den er slukket,
//             og slukker den, hvis den er tændt. Husk at svare browseren.
//             Tilføj adressen "/toggle" i setup().


// OPGAVE 5.2: Lav en funktion sendHilsen(), som sender en besked til skærmen.
//             Tilføj adressen "/hilsen" i setup().


// OPGAVE 5.3: Lav en funktion visStatus(), som svarer med LED'ens og
//             BOOT-knappens status i JSON-format. Tilføj adressen "/status" i setup().


void haandterBesked(String afsender, String tekst) {
  if (tekst == "BLINK") {
    blink(5);
  }
}

void loop() {
  holdForbindelse();
  hjemmeside.handleClient();  // Tjek om nogen har besøgt hjemmesiden
}


// ==========================================================================
// Hjælpefunktioner. Du behøver ikke ændre noget herunder.
// ==========================================================================

WiFiClient forbindelse;  // Forbindelsen til serveren

// Blinker LED'en et bestemt antal gange (fra del 2)
void blink(int antal) {
  for (int i = 0; i < antal; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }
}

// Giver 'true', hvis BOOT-knappen bliver trykket (fra del 2)
bool knapErTrykket() {
  if (digitalRead(KNAP_PIN) == LOW) {
    delay(50);
    while (digitalRead(KNAP_PIN) == LOW) {
      delay(10);
    }
    return true;
  }
  return false;
}

// Sender en besked, som bliver vist på skærmen
void sendTilServer(String tekst) {
  forbindelse.println(tekst);
}

// Sender en besked til én bestemt person
void sendTilPerson(String navn, String tekst) {
  forbindelse.println("@" + navn + "|" + tekst);
}

// Læser det, du skriver i Serial Monitor. Giver "" hvis der ikke er skrevet noget.
String laesFraSerialMonitor() {
  if (Serial.available() == 0) {
    return "";
  }
  String tekst = Serial.readStringUntil('\n');
  tekst.trim();
  return tekst;
}

// Stopper programmet med en fejlbesked, hvis opgave 3.1 ikke er udfyldt
void tjekOplysninger() {
  if (String(WIFI_NAVN) == "" || String(SERVER_IP) == "" || SERVER_PORT == 0 || MIT_NAVN == "") {
    while (true) {
      Serial.println("Mangler oplysninger: Udfyld WIFI_NAVN, WIFI_KODE, SERVER_IP, SERVER_PORT og MIT_NAVN (opgave 3.1).");
      delay(3000);
    }
  }
}

void forbindTilWiFi() {
  WiFi.begin(WIFI_NAVN, WIFI_KODE);
  Serial.print("Forbinder til WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Forbundet til WiFi. Min IP-adresse er ");
  Serial.println(WiFi.localIP());
}

void forbindTilServer() {
  Serial.print("Forbinder til serveren ");
  Serial.print(SERVER_IP);
  Serial.print(":");
  Serial.println(SERVER_PORT);
  if (forbindelse.connect(SERVER_IP, SERVER_PORT)) {
    forbindelse.println(MIT_NAVN);  // Den første linje fortæller serveren, hvem vi er
    Serial.println("Forbundet til serveren.");
  } else {
    Serial.println("Kunne ikke forbinde. Prøver igen om 2 sekunder.");
    delay(2000);
  }
}

// Sørger for at vi er forbundet, og tager imod nye beskeder.
// Hver besked fra serveren ser sådan ud: "afsender|tekst"
void holdForbindelse() {
  if (!forbindelse.connected()) {
    forbindTilServer();
    return;
  }
  while (forbindelse.available()) {
    String linje = forbindelse.readStringUntil('\n');
    linje.trim();
    int skille = linje.indexOf('|');
    if (skille < 0) {
      continue;
    }
    String afsender = linje.substring(0, skille);
    String tekst = linje.substring(skille + 1);
    Serial.println("Besked fra " + afsender + ": " + tekst);
    haandterBesked(afsender, tekst);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(KNAP_PIN, INPUT_PULLUP);
  delay(2000);
  tjekOplysninger();
  forbindTilWiFi();
  forbindTilServer();

  // Fortæl hjemmesiden, hvilken funktion der skal køres for hver adresse
  hjemmeside.on("/", visSide);
  // OPGAVE 5.1, 5.2 og 5.3: Tilføj dine adresser her

  hjemmeside.begin();

  Serial.print("Hjemmesiden kører. Åbn denne adresse på din telefon: http://");
  Serial.println(WiFi.localIP());
}
