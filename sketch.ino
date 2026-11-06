
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22
#define LED_PIN 26

const float TEMP_THRESHOLD = 30.0;  // alarm threshold (°C)

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqtt_server = "broker.hivemq.com";

const char* topic_temp  = "emri123/iot/temperature";
const char* topic_hum   = "emri123/iot/humidity";
const char* topic_alert = "emri123/iot/alert";

DHT dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient client(espClient);

void connectWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password, 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" OK!");
}

void connectMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    String id = "esp32-" + String(random(0xffff), HEX);
    if (client.connect(id.c_str())) {
      Serial.println(" OK!");
    } else {
      Serial.println(" failed, retrying...");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  dht.begin();
  connectWiFi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) connectMQTT();
  client.loop();

  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(t) || isnan(h)) {
    Serial.println("Sensor reading error!");
  } else {
    bool alarm = t > TEMP_THRESHOLD;
    digitalWrite(LED_PIN, alarm ? HIGH : LOW);

    Serial.printf("Temperature: %.1f C, Humidity: %.1f %%, Alarm: %s\n",
                  t, h, alarm ? "ON" : "OFF");

    client.publish(topic_temp, String(t).c_str());
    client.publish(topic_hum, String(h).c_str());
    client.publish(topic_alert, alarm ? "ALERT" : "OK");
  }
  delay(3000);
}
