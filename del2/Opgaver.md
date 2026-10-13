# Del 2 – Styr LED'en

I denne del arbejder du alene med din egen ESP32. Du skal skrive tre små stykker kode, som tilsammen får LED'en til at blinke, når du trykker på en knap. Den kode, du skriver her, bliver brugt igen i del 3 og 4.

Åbn filen `del2/del2_skelet/del2_skelet.ino`. Næsten al koden er skrevet. Du skal kun udfylde de steder, hvor der står `OPGAVE`.

Lav opgaverne i rækkefølge, og upload programmet efter hver opgave, så du kan se, hvad der sker.

Hvis du ikke kan komme videre, så kig i [Hints.md](Hints.md). Den fulde løsning står i [Løsninger.md](Løsninger.md).

---

## Opgave 2.1 – Sluk LED'en

Upload skelettet, som det er. LED'en tænder, men den slukker aldrig.

Find funktionen `blinkEnGang`. Den tænder LED'en og venter, men den mangler linjen, der slukker LED'en igen. Tilføj den linje.

**Resultat:** LED'en blinker.

---

## Opgave 2.2 – Blink et bestemt antal gange

Find funktionen `blink(int antal)`. Den skal blinke LED'en så mange gange, som `antal` siger, men lige nu blinker den kun én gang.

Lav en **for-løkke** omkring linjen `blinkEnGang(200);`, så den bliver gentaget `antal` gange.

**Resultat:** LED'en blinker 3 gange, holder en pause og blinker 3 gange igen.

---

## Opgave 2.3 – Brug knappen

Find `loop()`. Lige nu blinker LED'en hele tiden. Den skal kun blinke, når du trykker på **BOOT**-knappen på boardet.

Lav et **if-statement** omkring de to linjer i `loop()`. Brug funktionen `knapErTrykket()`, som allerede er skrevet.

**Resultat:** LED'en blinker 3 gange, hver gang du trykker på BOOT-knappen.

---

## Ekstraopgave 2.4 – Tæl antal tryk (svær)

Lav programmet om, så LED'en blinker én gang ved første tryk, to gange ved andet tryk, tre gange ved tredje tryk og så videre. Skriv antallet af tryk i Serial Monitor.
