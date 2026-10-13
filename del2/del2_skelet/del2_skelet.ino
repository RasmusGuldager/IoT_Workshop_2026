// Del 2 - Styr LED'en
//
// Det meste af koden er skrevet. Du skal kun udfylde de steder,
// hvor der står "OPGAVE". Lav opgaverne i rækkefølge, og upload efter hver.

const int LED_PIN = 15;   // Den indbyggede LED
const int KNAP_PIN = 9;   // BOOT-knappen på boardet


// Tænder LED'en, venter, slukker LED'en og venter igen.
// 'tid' er hvor mange millisekunder den skal være tændt og slukket.
void blinkEnGang(int tid) {
  digitalWrite(LED_PIN, HIGH);
  delay(tid);

  // OPGAVE 2.1: Sluk LED'en her (én linje)

  delay(tid);
}


// Blinker LED'en et bestemt antal gange.
void blink(int antal) {
  // OPGAVE 2.2: Lav en for-løkke omkring linjen herunder,
  //             så den bliver gentaget 'antal' gange.
  blinkEnGang(200);
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
  // OPGAVE 2.3: Sæt et if-statement omkring de to linjer herunder,
  //             så de kun bliver kørt, når knappen bliver trykket.
  blink(3);
  delay(1000);
}
