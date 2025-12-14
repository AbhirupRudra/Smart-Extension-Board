# 🔌 Smart Extension Board using ESP8266 & Blynk

Control up to **4 electrical appliances wirelessly** using your smartphone with this **ESP8266-based Smart Extension Board** powered by **Blynk IoT Cloud**.  
Simple, reliable, and perfect for beginners in IoT & home automation.

---

## 🚀 Features

- 📱 **Mobile App Control** using Blynk
- 🔘 **4 Independent Outputs** (LEDs / Relays)
- ☁️ **Cloud-Based Control** (Blynk.Cloud)
- ⚡ **Real-Time Response**
- 🧠 **Minimal & Clean Code**
- 🔌 Ideal for **Smart Home / Smart Plug Projects**

---

## 🛠️ Hardware Required

- ESP8266 (NodeMCU / ESP-12 / ESP-07)
- 4-Channel Relay Module or 4 LEDs
- Jumper Wires
- Power Supply (5V for relay module)

---

## 🔗 Pin Configuration

| Blynk Button | Virtual Pin | ESP8266 GPIO |
|--------------|-------------|--------------|
| Plug 1       | V0          | GPIO14 (D5) |
| Plug 2       | V1          | GPIO12 (D6) |
| Plug 3       | V2          | GPIO13 (D7) |
| Plug 4       | V3          | GPIO15 (D8) |

> Relay modules are **Active LOW** (LOW = ON, HIGH = OFF)

---

## 📲 Blynk App Setup

1. Create a new template in **Blynk IoT**
2. Add **4 Button Widgets**
3. Set buttons to **Switch mode**
4. Assign Virtual Pins:
   - Button 1 → `V0`
   - Button 2 → `V1`
   - Button 3 → `V2`
   - Button 4 → `V3`
5. Copy **Template ID** and **Auth Token** into the code

---

## ⚙️ How It Works

Each Blynk button sends a digital command to the ESP8266 over the internet.  
The ESP8266 receives the command and toggles the corresponding GPIO pin, turning the connected relay or LED **ON or OFF instantly**.

---

## 📸 Demo Ideas

- Smart Room Light Control  
- WiFi Controlled Power Strip  
- Remote Lab Equipment Switch  
- Hostel / Home Automation Starter Project  

---

## 📌 Future Enhancements

- Manual push button control
- EEPROM power-fail memory
- Energy monitoring
- Google Assistant / Alexa support
- Web dashboard

---

## ⭐ If You Like This Project

Give it a ⭐ on GitHub — it helps others discover it!

---

## 👤 Author

**Abhirup**  
ECE | IoT & Embedded Systems  
ESP8266 • ESP32 • Arduino • Blynk • Automation

---

## 🏷️ Tags

`ESP8266` `Blynk` `IoT` `Home Automation` `Smart Plug` `Relay Control` `Embedded Systems`
