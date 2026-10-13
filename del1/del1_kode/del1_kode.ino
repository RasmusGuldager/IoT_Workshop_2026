// Del 1 - Dit første program
//
// Dette program er færdigt. Det får den lille lampe (LED) på boardet til at
// blinke og skriver en besked til computeren én gang i sekundet.
//
// Opgave 1.2: Skriv dit navn mellem anførselstegnene i linjen herunder.

String MIT_NAVN = "Skriv dit navn her";


// --------------------------------------------------------------------------
// Du behøver ikke ændre noget herunder.
// --------------------------------------------------------------------------

const int LED_PIN = 15;  // Den indbyggede LED sidder på pin 15
int sekunder = 0;

void setup() {
  Serial.begin(115200);      // Start forbindelsen til computeren
  pinMode(LED_PIN, OUTPUT);  // Pin 15 skal styre LED'en
}

void loop() {
  digitalWrite(LED_PIN, HIGH);  // Tænd LED'en
  delay(500);                   // Vent et halvt sekund
  digitalWrite(LED_PIN, LOW);   // Sluk LED'en
  delay(500);                   // Vent et halvt sekund

  sekunder = sekunder + 1;
  Serial.println("Hej " + MIT_NAVN + ". Din ESP32 har kørt i " + String(sekunder) + " sekunder.");
}
