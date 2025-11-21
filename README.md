# Smart IoT-Based Energy Monitoring & Load Protection System (ESP32 + Wokwi)

A simulation-based **ESP32 project** that monitors current, calculates power, displays values on an OLED, and trips a relay when current exceeds a threshold. Designed for simulation in **Wokwi** and hardware-ready for real-world deployment.

---

## Features

- Real-time **current and power monitoring**  
- Automatic **load disconnect** via relay when overcurrent occurs  
- **OLED display** for current, power, and threshold values  
- **Buzzer and LED alerts** for overload events  
- Simulation-ready (Wokwi) and hardware-ready (Arduino/ESP32)  
- Cloud-ready architecture for future **IoT integration**  

---

## Components Used

| Component         | Quantity |
|------------------|----------|
| ESP32 Dev Board   | 1        |
| Potentiometer (simulates ACS712 current sensor) | 1 |
| SSD1306 OLED Display (128×64) | 1 |
| Relay Module      | 1        |
| LED (+ 220Ω resistor) | 1     |
| Buzzer            | 1        |
| Jumper Wires      | Several  |

---

## Wiring / Pin Mapping (Wokwi)

| ESP32 Pin  | Component             |
|-----------|----------------------|
| 3.3V      | Potentiometer VCC, OLED VCC |
| GND       | Pot GND, OLED GND, Relay GND, LED GND, Buzzer GND |
| ADC34     | Potentiometer middle pin (current simulation) |
| GPIO21    | OLED SDA             |
| GPIO22    | OLED SCL             |
| GPIO5     | Relay IN             |
| GPIO2     | LED (+ via 220Ω)     |
| GPIO15    | Buzzer               |

> Adjust ADC pin if needed; in Wokwi, ADC pins may vary.  

---

## How It Works

1. **Startup**: Displays welcome message on OLED.  
2. **Current Reading**: Reads analog input from potentiometer (simulates ACS712).  
3. **Power Calculation**: Calculates power using `Power = Voltage × Current`.  
4. **Display & Logging**: Shows real-time current, power, and threshold values on OLED and Serial Monitor.  
5. **Overload Detection**:  
   - If current exceeds threshold, relay switches OFF to disconnect load, LED turns OFF, and buzzer turns ON.  
   - If current is below threshold, relay ON, LED ON, buzzer OFF.  
6. **Optional Enhancements**:  
   - Hysteresis for relay stability  
   - Cloud integration (ThingSpeak/Blynk)  
   - Adjustable threshold via buttons or menu  
---

## 👤 Author

**Sattwik**  

