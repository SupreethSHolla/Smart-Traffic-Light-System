# Smart Adaptive Traffic Control System

An Arduino UNO based smart traffic management system developed in Tinkercad using embedded C programming.

---

# Features

- 🚦 Two-road traffic signal system
- 🚑 Ambulance priority override
- 🚶 Pedestrian crossing support
- 📟 16x2 LCD status display
- 🔊 Buzzer alerts
- 📡 HC-SR04 vehicle detection
- 🌙 Automatic idle yellow mode
- ⚡ Real-time traffic monitoring

---

# 🛠 Components Used

- Arduino UNO
- HC-SR04 Ultrasonic Sensors
- 16x2 LCD Display
- LEDs
- Push Buttons
- Buzzer
- Potentiometer
- Breadboard
- Jumper Wires

---

# Working

## Normal Mode
Traffic alternates between:
- Road 1
- Road 2

## Ambulance Mode
Emergency buttons provide:
- Instant green signal
- Priority vehicle clearance

## Pedestrian Mode
Pedestrian button:
- Stops traffic
- Enables safe crossing

## Idle Mode
If both roads are empty:
- Yellow LEDs blink
- System resumes automatically on vehicle detection

---

# Pin Configuration

| Component | Pin |
|---|---|
| R1 Red | 7 |
| R1 Yellow | 9 |
| R1 Green | 11 |
| R2 Red | 12 |
| R2 Yellow | 13 |
| R2 Green | A0 |
| Pedestrian Button | A2 |
| Ambulance Button 1 | 10 |
| Ambulance Button 2 | 1 |
| Buzzer | A1 |
| Sensor1 Trigger | A3 |
| Sensor1 Echo | A4 |
| Sensor2 Trigger | 0 |
| Sensor2 Echo | A5 |

---

# Technologies Used

- Arduino IDE
- Embedded C
- Tinkercad
- Sensor Interfacing
- Embedded Systems

---

# Project Preview

<img width="1912" height="851" alt="Embedded Project Final" src="https://github.com/user-attachments/assets/3adc958f-111e-4885-9870-f76801ae85d8" />

---

# Flowchart 

<img width="1024" height="1536" alt="Embedded Project Flowchart" src="https://github.com/user-attachments/assets/a1eebbac-9c89-4291-9516-b98335634169" />

---

# Concepts Used

- Embedded Systems
- Real-Time Monitoring
- Traffic Automation
- Sensor Interfacing
- LCD Communication
- Interrupt-Based Controls

---

# Future Improvements

- IoT integration
- Mobile app monitoring
- AI traffic prediction
- Camera-based detection
- Cloud analytics
