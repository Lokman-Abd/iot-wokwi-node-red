# Smart Home System Simulation with Wokwi

## Objective
To develop a comprehensive IoT-based Smart Home System simulation that integrates automated lighting, temperature monitoring, and a security alarm system using an ESP32 microcontroller and various sensors.

## Components Used
- ESP32 Microcontroller
- DHT22 Temperature and Humidity Sensor
- PIR Motion Sensor
- LDR (Light Dependent Resistor) Sensor
- LEDs
- Buzzer
- MQTT Broker (Node-RED)

## System Behavior and Logic

### Temperature and Humidity Monitoring
- Uses DHT22 sensor to continuously read temperature and humidity
- Publishes data to MQTT topics for remote monitoring

### Smart Lighting
- LDR sensor measures ambient light levels
- LEDs activate when:
  1. Light level is low (< 500)
  2. Motion is detected by PIR sensor

### Security Alarm
- PIR motion sensor triggers buzzer when motion is detected
- Provides immediate alert for potential security breaches

## MQTT Integration
- Publishes sensor data to topics:
  - `home/temperature`
  - `home/humidity`
  - `home/light`
- Enables remote monitoring and potential cloud integration

## Challenges and Considerations
- IoT Knowledge Limitations with complex pin configurations
- Simulator Configuration Challenges of Wokwi localy with vs code
- MQTT and Development Integration Problems
- VS Code and Wokwi synchronization data with node-red via a local broker Mosquitto 
- Limited understanding of IoT communication protocols
- Ensure stable WiFi and MQTT broker connection that's way all the work done localy without need to online broker
