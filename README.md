# Smart Agriculture System 🌱

An IoT-based Smart Agriculture / Smart Irrigation System that automates irrigation using soil moisture monitoring and cloud connectivity.

## 📌 Overview

This project helps farmers and users monitor soil moisture levels and automatically control the water pump when the soil becomes dry.
The system uses sensors and IoT technology to reduce water wastage and improve irrigation efficiency.

## 🚀 Features

- Automatic irrigation system
- Soil moisture monitoring
- Water pump automation
- Real-time data monitoring
- Firebase cloud integration
- IoT-based smart farming
- Low-cost and efficient solution

## 🛠️ Technologies Used

- Arduino IDE
- ESP8266 / NodeMCU
- Firebase Realtime Database
- Embedded C/C++
- IoT

## 🔧 Components Used

- NodeMCU ESP8266
- Soil Moisture Sensor
- DHT11
- Relay Module
- Water Pump
- Jumper Wires
- Power Supply

## ⚙️ Working Principle

1. Soil moisture sensor continuously checks soil moisture level.
2. If soil becomes dry, the sensor sends data to NodeMCU.
3. NodeMCU turns ON the water pump using relay module.
4. Data is uploaded to Firebase cloud database.
5. When moisture becomes sufficient, pump turns OFF automatically.

## ☁️ Firebase Integration

Firebase Realtime Database is used for:
- Storing sensor data
- Real-time monitoring
- Cloud connectivity
- IoT communication

## 📂 Project Structure

```text
Smart-Agriculture-System/
│
├── Arduino_Code/
├── Circuit_Diagram/
├── Images/
├── README.md
├── secrets_example.h
└── Project_Report.pdf
