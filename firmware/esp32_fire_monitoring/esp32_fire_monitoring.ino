#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "config.h"

// Pin definitions
#define FLAME_PIN 25
#define ONE_WIRE_BUS 26
#define LED_PIN 2
#define BUZZER_PIN 19

WiFiClientSecure espClient;
PubSubClient client(espClient);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

bool flameDetected = false;
float temperature = 0.0;
bool alarmActive = false;
unsigned long lastPublish = 0;

String getTimestamp() {
  unsigned long ms = millis();
  unsigned long seconds = ms / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = minutes / 60;

  ms = ms % 1000;
  seconds = seconds % 60;
  minutes = minutes % 60;
  hours = hours % 24;

  char buffer[30];
  sprintf(buffer, "%02lu:%02lu:%02lu,%03lu", hours, minutes, seconds, ms);
  return String(buffer);
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.printf("%s [MQTT] Client esp32 received PUBLISH\n", getTimestamp().c_str());

  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  StaticJsonDocument<200> doc;
  if (!deserializeJson(doc, message)) {
    if (doc.containsKey("command") && doc["command"] == "reset") {
      digitalWrite(LED_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);
      alarmActive = false;
    }

    if (doc.containsKey("buzzer")) {
      String state = doc["buzzer"];
      digitalWrite(BUZZER_PIN, state == "on" ? HIGH : LOW);
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(FLAME_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  sensors.begin();

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  espClient.setInsecure();

  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(mqttCallback);
  client.setKeepAlive(60);
}

void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }

  client.loop();
  readSensors();
  controlAlarm();

  if (millis() - lastPublish > 5000) {
    publishMQTT();
    lastPublish = millis();
  }
}

void reconnectMQTT() {
  while (!client.connected()) {
    String clientId = "esp32_fire_alarm";

    Serial.printf(
      "%s [MQTT] Sending CONNECT client_id=%s\n",
      getTimestamp().c_str(),
      clientId.c_str()
    );

    if (client.connect(clientId.c_str(), MQTT_USERNAME, MQTT_PASSWORD, NULL, 0, true, NULL, true)) {
      Serial.printf("%s [MQTT] Connected to broker\n", getTimestamp().c_str());
      client.subscribe(MQTT_CONTROL_TOPIC, 1);
      Serial.printf("%s [MQTT] Subscribed: %s\n", getTimestamp().c_str(), MQTT_CONTROL_TOPIC);
    } else {
      Serial.printf("%s [MQTT] Connection failed, rc=%d\n", getTimestamp().c_str(), client.state());
      delay(5000);
    }
  }
}

void publishMQTT() {
  StaticJsonDocument<300> doc;
  doc["flame"] = flameDetected;
  doc["temperature"] = temperature;
  doc["alarm"] = alarmActive;
  doc["timestamp"] = millis();
  doc["device"] = "ESP32_FireAlarm";

  char buffer[300];
  size_t n = serializeJson(doc, buffer);

  Serial.printf(
    "%s [MQTT] Publishing to %s (%d bytes)\n",
    getTimestamp().c_str(),
    MQTT_TOPIC,
    n
  );

  if (client.publish(MQTT_TOPIC, buffer, false)) {
    Serial.printf("%s [MQTT] Publish OK\n", getTimestamp().c_str());
  }
}

void readSensors() {
  flameDetected = (digitalRead(FLAME_PIN) == LOW);

  sensors.requestTemperatures();
  float tempRead = sensors.getTempCByIndex(0);
  if (tempRead != -127.0 && tempRead != 85.0) {
    temperature = tempRead;
  }
}

void controlAlarm() {
  if (flameDetected || temperature > 50.0) {
    alarmActive = true;

    static unsigned long lastBlink = 0;
    if (millis() - lastBlink > 300) {
      lastBlink = millis();
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      digitalWrite(BUZZER_PIN, !digitalRead(BUZZER_PIN));
    }
  } else {
    alarmActive = false;
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }
}
