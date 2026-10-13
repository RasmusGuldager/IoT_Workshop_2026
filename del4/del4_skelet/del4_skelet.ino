// Del 4 - Tal med hinanden
//
// Koden fortsætter fra del 3. Kopiér dine oplysninger fra opgave 3.1 ind herunder.
// Udfyld derefter de steder, hvor der står "OPGAVE".

#include <WiFi.h>

// Udfyld oplysningerne fra tavlen (de samme som i del 3).
// Tekst skal stå mellem anførselstegn, tal skal ikke.
const char* WIFI_NAVN   = "";
const char* WIFI_KODE   = "";
const char* SERVER_IP   = "";
const int   SERVER_PORT = 0;
String MIT_NAVN         = "";

// OPGAVE 4.1: Skriv navnet på din makker. Det skal staves præcis,
//             som det står på skærmen.
String MAKKER = "";

const int LED_PIN = 15;   // Den indbyggede LED
const int KNAP_PIN = 9;   // BOOT-knappen på boardet


// ==========================================================================
// Din kode
// ==========================================================================

// Denne funktion bliver kørt, hver gang der kommer en besked fra serveren.
void haandterBesked(String afsender, String tekst) {
  if (tekst == "BLINK") {
    blink(5);
  }

  // OPGAVE 4.3: Hvis tekst er "PING", skal du sende "PONG" tilbage til afsenderen.

}

void loop() {
  holdForbindelse();  // Skal altid stå først i loop()

  if (knapErTrykket()) {
    // OPGAVE 4.1: Send "BLINK" til din makker, når du trykker på knappen.

  }

  String tekst = laesFraSerialMonitor();
  if (tekst != "") {
    // OPGAVE 4.2: Send det, du har skrevet i Serial Monitor, til din makker.

  }
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
}
