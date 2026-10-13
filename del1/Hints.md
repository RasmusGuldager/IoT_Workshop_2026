# Del 1 – Hints

## Opgave 1.1 – Hvis det ikke virker

| Problem | Løsning |
|---|---|
| Der er ingen port at vælge under **Tools → Port** | Prøv et andet USB-kabel. Nogle kabler kan kun oplade og kan ikke sende data. Prøv også en anden USB-indgang på computeren. |
| Upload fejler | Hold **BOOT**-knappen på boardet nede, mens du sætter USB-kablet i. Slip knappen, og prøv at uploade igen. |
| Serial Monitor er tom | Tjek at **Tools → USB CDC On Boot** står på **Enabled**, og upload igen. |
| Der står mærkelige tegn i Serial Monitor | Vælg **115200 baud** nederst i Serial Monitor. |
| Porten forsvinder efter upload | Vælg porten igen under **Tools → Port**. |
| Linux: *Permission denied* | Skriv `sudo usermod -aG dialout $USER` i en terminal, og log ud og ind igen. |
| **esp32** dukker ikke op i Boards Manager | Gå til **File → Preferences**, og indsæt `https://espressif.github.io/arduino-esp32/package_esp32_index.json` i feltet *Additional boards manager URLs*. Prøv derefter igen. |

## Opgave 1.2 – Tekst i kode

Tekst i kode skal altid stå mellem to anførselstegn `"`. Alt mellem anførselstegnene bliver brugt præcis, som det står.

```cpp
String MIT_NAVN = "Anna";
```

Linjen skal slutte med et semikolon `;`. Det fortæller computeren, at linjen er slut.
