# 🚦 Arduino LED Sequence with I2C LCD Display

An interactive Arduino project that cycles through Red, Yellow, and Green LEDs while displaying their status in real-time on both an I2C 16x2 LCD and the Serial Monitor.

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Language: C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://isocpp.org/)
[![Platform: Arduino](https://img.shields.io/badge/Platform-Arduino-orange.svg)](https://www.arduino.cc/)

---

## 📖 Description

This project demonstrates how to sequentially control three LEDs (Red, Yellow, Green) using an Arduino. The LED states are updated every 2 seconds and visually displayed on:

- 🖥️ A 16x2 I2C LCD screen  
- 📟 The Serial Monitor (9600 baud)

Each LED follows a timed cycle:  
**Red → Yellow → Green**  
Each state is displayed with an ON/OFF status indicator.

---

## ✨ Features

✅ Automatic LED sequencing (2-second intervals)  
✅ Real-time status output to I2C LCD and Serial Monitor  
✅ Clean separation of logic for control and display  
✅ Simple and scalable for further expansion  

---

## 🛠 Components Required

| Component             | Quantity |
|-----------------------|----------|
| Arduino Uno/Nano      | 1        |
| 16x2 I2C LCD Display  | 1        |
| LEDs (Red, Yellow, Green) | 3    |
| Resistors (220Ω)      | 3        |
| Breadboard + Wires    | As needed |
| USB Cable             | 1        |

---

## 🔌 Wiring Guide

### 🔴 LED Connections

| LED Color | Arduino Pin | Resistor |
|-----------|-------------|----------|
| Red       | D2          | 220Ω     |
| Yellow    | D3          | 220Ω     |
| Green     | D4          | 220Ω     |

### 📺 I2C LCD Connections

| LCD Pin | Arduino Pin     |
|---------|------------------|
| GND     | GND              |
| VCC     | 5V               |
| SDA     | A4 (Uno/Nano)    |
| SCL     | A5 (Uno/Nano)    |

> ⚠️ **Note:** If your LCD doesn’t display anything, use an I2C scanner sketch to detect its address. Default: `0x27`.

---

## 💡 Code Overview

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int ledPins[] = {2, 3, 4};
const char* ledNames[] = {"Czerwona", "Zolta", "Zielona"};
int ledIndex = 0;
bool ledState = true;
unsigned long previousMillis = 0;
const long interval = 2000;

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);

  for (int i = 0; i < 3; i++) pinMode(ledPins[i], OUTPUT);

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

    if (!ledState) ledIndex = (ledIndex + 1) % 3;

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
