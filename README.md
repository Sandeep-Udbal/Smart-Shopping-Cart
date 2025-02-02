# 🛒 Smart Shopping Cart Bot

## 📌 Overview
The **Smart Shopping Cart Bot** automates the shopping experience by scanning products using RFID, displaying item details, and calculating the total bill. It features a **Bluetooth-controlled system** with an **ESP32 and Arduino Uno**, enabling a seamless checkout process and reducing queue time.

## 🔧 Features
- 📡 **RFID-based Product Scanning** – Automatically scans multiple items.
- 📟 **I2C Display** – Shows product name and price in real-time.
- 🔄 **Servo Motor for Cart Access** – Opens the trolley when an item is added.
- 📶 **Bluetooth Connectivity** – Enables wireless control and integration.g
- 🛍 **Automated Billing** – Calculates the total price based on scanned items.

## 🛠 Components Used
- **ESP32 Dev Kit V1** – Handles Bluetooth communication and controls the cart.
- **Arduino Uno** – Manages RFID scanning and data processing.
- **RFID Module (RC522)** – Reads product tags.
- **Servo Motor** – Opens the cart for product placement.
- **I2C Display (16x2 or OLED)** – Displays product details.

## 📜 How It Works
1. **Scan Items**: The RFID module detects product tags when placed inside the cart.
2. **Process Data**: The Arduino processes the scanned item and sends data to ESP32.
3. **Display Information**: The I2C screen shows the product name and price.
4. **Billing & Checkout**: The system calculates the total bill for easy checkout.

## 🚀 Future Enhancements
- 📲 **Mobile App Integration** – Display total price and track purchases.
- 🤖 **Autonomous Navigation** – Implement self-driving cart movement.
- ⚖️ **Weight Sensors** – Verify items added to the cart.
```

## 📌 Getting Started
### 🛠 Prerequisites
- Install **Arduino IDE** and **ESP32 Board Package**
- Install necessary libraries: `RFID`, `Wire`, `Servo` for Arduino.

### 🚀 Installation
1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/SmartShoppingCartBot.git
   ```
2. Upload the **Arduino Uno code** to the board.
3. Upload the **ESP32 firmware** using the Arduino IDE.
4. Connect the RFID module, display, and servo motor as per the circuit diagram.

## 🤝 Contributing
Feel free to submit issues, pull requests, or feature suggestions!

