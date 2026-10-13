// Del 3 - Løsning (opgave 3.1, 3.2 og 3.3)

#include <WiFi.h>

// Oplysningerne fra tavlen (opgave 3.1):
const char* WIFI_NAVN   = "IoT-Workshop";
const char* WIFI_KODE   = "12345678";
const char* SERVER_IP   = "192.168.1.100";
const int   SERVER_PORT = 5000;
String MIT_NAVN         = "Anna";

const int LED_PIN = 15;   // Den indbyggede LED
const int KNAP_PIN = 9;   // BOOT-knappen på boardet


// ==========================================================================
// Din kode
// ==========================================================================

// Denne funktion bliver kørt, hver gang der kommer en besked fra serveren.
// 'afsender' er navnet på den, der har sendt beskeden.
// 'tekst' er selve beskeden.
void haandterBesked(String afsender, String tekst) {
  if (tekst == "BLINK") {  // Opgave 3.3
    blink(5);
  }
}

void loop() {
  holdForbindelse();  // Skal altid stå først i loop()

  if (knapErTrykket()) {
    sendTilServer("Hej fra " + MIT_NAVN);  // Opgave 3.2
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
