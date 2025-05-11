# Arduino LED Sequence with I2C LCD Display

**An Arduino project that cycles through three LEDs (Red, Yellow, Green) and displays their state on an I2C 16x2 LCD and Serial Monitor.**

## Description

This project demonstrates how to sequentially control three LEDs using an Arduino and visually represent their status on a 16x2 I2C LCD. The LED status (ON/OFF) updates every 2 seconds and is displayed both on the LCD and the Serial Monitor. Each LED lights up in a repeating cycle: **Red → Yellow → Green**.

## Components Required

- Arduino board (e.g., Uno, Nano)
- 3 LEDs (Red, Yellow, Green)
- 3 resistors (220Ω recommended)
- I2C 16x2 LCD (address: `0x27`)
- Breadboard and jumper wires
- USB cable for programming

## Features

- ✅ Automatic LED cycling with 2-second intervals
- ✅ Real-time status display on LCD and Serial Monitor
- ✅ Clean separation of LED control and display logic

## Wiring

### LED Connections

| LED Color | Arduino Pin | Resistor | 
|-----------|-------------|----------|
| Red       | D2          | 220Ω     |
| Yellow    | D3          | 220Ω     |
| Green     | D4          | 220Ω     |

### I2C LCD Connections

| LCD Pin | Arduino Pin |
|---------|-------------|
| GND     | GND         |
| VCC     | 5V          |
| SDA     | A4 (Uno/Nano) |
| SCL     | A5 (Uno/Nano) |

> ⚠️ I2C address may vary. If your LCD does not respond, scan for its address using an I2C scanner sketch.

## Code Overview

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD I2C address

const int ledPins[] = {2, 3, 4};  // Pins for LEDs
const char* ledNames[] = {"Czerwona", "Zolta", "Zielona"};
int ledIndex = 0;
bool ledState = true;
unsigned long previousMillis = 0;
const long interval = 2000;  // 2-second interval

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);

  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  digitalWrite(ledPins[ledIndex], HIGH);
  lcd.print(ledNames[ledIndex]);
  lcd.print(" - ON");
  Serial.println(String(ledNames[ledIndex]) + " - ON");
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    digitalWrite(ledPins[ledIndex], LOW);
    lcd.clear();
    lcd.print(ledNames[ledIndex]);
    lcd.print(" - OFF");
    Serial.println(String(ledNames[ledIndex]) + " - OFF");

    if (!ledState) {
      ledIndex = (ledIndex + 1) % 3;
    }

    ledState = !ledState;
    digitalWrite(ledPins[ledIndex], ledState ? HIGH : LOW);

    if (ledState) {
      lcd.clear();
      lcd.print(ledNames[ledIndex]);
      lcd.print(" - ON");
      Serial.println(String(ledNames[ledIndex]) + " - ON");
    }
  }
}
```

## Installation

1. Open the Arduino IDE.
2. Install the `LiquidCrystal_I2C` library via **Tools > Manage Libraries**.
3. Upload the code to your Arduino board.
4. Observe LED behavior and monitor output via the LCD and Serial Monitor (9600 baud).

## License

This project is open-source and available under the MIT License.

---

> 💡 You can extend this project by adding buttons to control LED switching manually or by integrating more sensors.

