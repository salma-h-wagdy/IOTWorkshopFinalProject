# IoT Workshop Final Project

This project was developed as part of a 5-day intensive IoT workshop. The goal was to demonstrate real-world IoT concepts by building a system that connects an ESP microcontroller to a mobile app using the MQTT protocol.

## Overview

- **Device:** ESP (specifically ESP8266)
- **Sensors/Actuators:** IR sensor, LED
- **Communication:** WiFi, MQTT (via [broker.emqx.io](https://www.emqx.io/))
- **Mobile App:** Used to control the LED (switch) and receive IR sensor status which lights up a LED on the app when there's an object

## Features

- Publishes IR sensor state to an MQTT topic (`/topic-name/IR`)
- Subscribes to a switch topic (`/topic-name/switch`) to control an LED from the mobile app
- Demonstrates MQTT publish/subscribe model

## How It Works

1. **Connects to WiFi** using provided credentials.
2. **Connects to MQTT broker** and subscribes to the switch topic.
3. **Publishes IR sensor state** ("object" or "noobject") at regular intervals.
4. **Receives switch commands** from the mobile app to turn the LED on or off.

## Setup

1. Update your WiFi credentials in the code:
    ```cpp
    #define ssid "your-ssid"
    #define pass "your-password"
    ```
2. Insert unique client-id here to connect to the broker:
    ```cpp
    client.connect("unique-client-id")
    ```
2. Flash the code to your ESP.
3. Use a mobile app (like IoT MQTT Panel) to:
    - Subscribe to `/topic-name/IR` to view sensor status.
    - Publish "on"/"off" to `/topic-name/switch` to control the LED.

## Dependencies

- [PubSubClient](https://pubsubclient.knolleary.net/)
- [ESP8266WiFi](https://arduino-esp8266.readthedocs.io/en/latest/)

## Workshop Content

- Introduction to IoT and the IoT value chain
- Hardware and networking (OSI & TCP/IP layers)
- WiFi and MQTT (with hands-on implementation)
- Advanced MQTT (topic layers, QoS, retained messages, LWT)
- SSH into Raspberry Pi and remote development

---