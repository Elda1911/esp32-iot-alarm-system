# ESP32 IoT Temperature Alarm System

An IoT system that reads temperature and humidity with a DHT22 sensor,
publishes the data over MQTT in real time, and triggers an alarm
(LED + MQTT alert message) when the temperature exceeds a threshold.

## Technologies
- ESP32, C++ (Arduino framework)
- DHT22 sensor, LED
- MQTT (HiveMQ public broker)
- Wokwi simulator

## How it works
Sensor -> ESP32 -> WiFi -> MQTT broker -> Dashboard

If temperature > 30 °C:
- the LED turns on
- `ALERT` is published to the alert topic

## Run it
1. Open the project in Wokwi: [PASTE YOUR WOKWI LINK HERE]
2. Press Play
3. Open the [HiveMQ web client](https://www.hivemq.com/demos/websocket-client/),
   connect and subscribe to `emri123/iot/#`
4. Raise the DHT22 temperature above 30 °C to trigger the alarm

## MQTT topics
| Topic | Description |
|-------|-------------|
| `emri123/iot/temperature` | Temperature in °C |
| `emri123/iot/humidity` | Relative humidity in % |
| `emri123/iot/alert` | `ALERT` or `OK` |

## Screenshots
![HiveMQ](screenshot-hivemq.png)
![Wokwi](screenshot-wokwi.png)

## Future improvements
- Node-RED dashboard
- Data storage and history charts
- Real hardware deployment
