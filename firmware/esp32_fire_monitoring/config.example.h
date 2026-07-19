#pragma once

// Copy this file to config.h and fill in your local values.
// Do not commit config.h because it contains Wi-Fi and MQTT credentials.

const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASS = "YOUR_WIFI_PASSWORD";

const char* MQTT_SERVER = "YOUR-HIVEMQ-CLUSTER.s1.eu.hivemq.cloud";
const uint16_t MQTT_PORT = 8883;
const char* MQTT_USERNAME = "YOUR_HIVEMQ_USERNAME";
const char* MQTT_PASSWORD = "YOUR_HIVEMQ_PASSWORD";

const char* MQTT_TOPIC = "home/fire_sensor/1";
const char* MQTT_CONTROL_TOPIC = "home/fire_control/1";
