// Del 2 - Løsning (opgave 2.1, 2.2 og 2.3)

const int LED_PIN = 15;   // Den indbyggede LED
const int KNAP_PIN = 9;   // BOOT-knappen på boardet


// Tænder LED'en, venter, slukker LED'en og venter igen.
// 'tid' er hvor mange millisekunder den skal være tændt og slukket.
void blinkEnGang(int tid) {
  digitalWrite(LED_PIN, HIGH);
  delay(tid);

  digitalWrite(LED_PIN, LOW);  // Opgave 2.1

  delay(tid);
}


// Blinker LED'en et bestemt antal gange.
void blink(int antal) {
  for (int i = 0; i < antal; i++) {  // Opgave 2.2
    blinkEnGang(200);
  }
}


// Giver 'true' (sand), hvis BOOT-knappen bliver trykket, ellers 'false' (falsk).
bool knapErTrykket() {
  if (digitalRead(KNAP_PIN) == LOW) {
    delay(50);
    while (digitalRead(KNAP_PIN) == LOW) {
      delay(10);  // Vent til knappen bliver sluppet igen
    }
    return true;
  }
  return false;
}


void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(KNAP_PIN, INPUT_PULLUP);
}


void loop() {
  if (knapErTrykket()) {  // Opgave 2.3
    blink(3);
    delay(1000);
  }
}
