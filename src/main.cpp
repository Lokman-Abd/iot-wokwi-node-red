#include <Arduino.h>
#include <DHT.h>
#include <WiFi.h>
#include <PubSubClient.h>
// Pins and Sensor Configuration
#define DHTPIN 15
#define DHTTYPE DHT22
#define PIR_PIN 27
#define LDR_PIN 34
#define LED1_PIN 16
#define LED2_PIN 17
#define BUZZER_PIN 26
DHT dht(DHTPIN, DHTTYPE);
// WiFi and MQTT Configuration
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "host.wokwi.internal"; // Use your MQTT broker
// const char* mqtt_server = "test.mosquitto.org";
WiFiClient espClient;
PubSubClient client(espClient);
// Function Declarations
void connectToWiFi();
void reconnectMQTT();
void triggerAlarm();
void setup() {
// Initialize serial communication and sensors
Serial.begin(115200);
dht.begin();
pinMode(PIR_PIN, INPUT);
pinMode(LED1_PIN, OUTPUT);
pinMode(LED2_PIN, OUTPUT);
pinMode(BUZZER_PIN, OUTPUT);
// Connect to Wi-Fi and MQTT
connectToWiFi();
client.setServer(mqtt_server, 1883);
}
void loop() {
// Ensure MQTT connection
if (!client.connected()) {
reconnectMQTT();
}
client.loop();
// Read sensors
float temperature = dht.readTemperature();
float humidity = dht.readHumidity();
int motionDetected = digitalRead(PIR_PIN);
int lightLevel = analogRead(LDR_PIN);
// Publish sensor data
client.publish("home/temperature", String(temperature).c_str());
client.publish("home/humidity", String(humidity).c_str());
client.publish("home/light", String(lightLevel).c_str());
// Print temperature and humidity
Serial.print("Temp: ");
Serial.print(temperature);
Serial.print(" °C, Humidity: ");
Serial.print(humidity);
Serial.println(" %");
Serial.print("Light Level: ");
Serial.println(lightLevel);
// Motion and light logic
if (motionDetected && lightLevel < 500) { // Adjust threshold as needed
Serial.println("Motion detected!");
digitalWrite(LED1_PIN, HIGH);
digitalWrite(LED2_PIN, HIGH);
triggerAlarm();
} else {
digitalWrite(LED1_PIN, LOW);
digitalWrite(LED2_PIN, LOW);
}
delay(2000); // Adjust delay as needed
}
void connectToWiFi() {
Serial.println("Connecting to WiFi...");
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.println("Attempting to connect...");
}
Serial.println("Connected to WiFi");
}
void reconnectMQTT() {
while (!client.connected()) {
Serial.println("Connecting to MQTT...");
if (client.connect("ESP32Client")) {
Serial.println("Connected to MQTT");
} else {
Serial.print("Failed MQTT connection, rc=");
Serial.println(client.state());
delay(5000); // Retry delay
}
}
}
void triggerAlarm() {
digitalWrite(BUZZER_PIN, HIGH);
Serial.println("Alarm triggered !!!!!");
delay(500);
digitalWrite(BUZZER_PIN, LOW);
}