#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Adres I2C może być inny

const int ledPins[] = {2, 3, 4};  // Piny do diod LED
const char* ledNames[] = {"Czerwona", "Zolta", "Zielona"};
int ledIndex = 0;  // Aktualny indeks diody, czerwona dioda jest pierwsza
bool ledState = true;  // Stan diody, true oznacza, że czerwona dioda zapali się na początku
unsigned long previousMillis = 0;
const long interval = 2000;  // Interwał zmiany stanów

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  // Zapal początkową diodę na starcie
  digitalWrite(ledPins[ledIndex], HIGH);
  lcd.print(ledNames[ledIndex]);
  lcd.print(" - ON");
  Serial.println(String(ledNames[ledIndex]) + " - ON");
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Wyłączenie bieżącej diody
    digitalWrite(ledPins[ledIndex], LOW);
    lcd.clear();
    lcd.print(ledNames[ledIndex]);
    lcd.print(" - OFF");
    Serial.println(String(ledNames[ledIndex]) + " - OFF");

    if (!ledState) {
      ledIndex = (ledIndex + 1) % 3;  // Przejście do następnej diody
    }

    // Zmiana stanu diody
    ledState = !ledState;
    digitalWrite(ledPins[ledIndex], ledState ? HIGH : LOW);

    // Aktualizacja stanu diody na ON w LCD i monitorze szeregowym
    if (ledState) {
      lcd.clear();
      lcd.print(ledNames[ledIndex]);
      lcd.print(" - ON");
      Serial.println(String(ledNames[ledIndex]) + " - ON");
    }
  }
}
