# Firmware

Thu muc nay chua code firmware duoc trich tu phu luc trong `Bao cao cuoi ki.docx`.

## Luu y ve nhan ten trong bao cao

Trong phu luc, doan code duoc dat tieu de `CODE STM32`. Tuy nhien noi dung code su dung cac thu vien:

- `WiFi.h`
- `WiFiClientSecure.h`
- `PubSubClient.h`
- `ArduinoJson.h`
- `OneWire.h`
- `DallasTemperature.h`

Vi vay source nay phu hop voi ESP32 chay Arduino IDE, khong phai project STM32CubeIDE/HAL. Bao cao co mo ta STM32 thu thap du lieu cam bien va gui UART sang ESP32, nhung minh khong tim thay file source STM32 HAL/C day du trong thu muc ban dau.

## Cau truc

- `esp32_fire_monitoring/esp32_fire_monitoring.ino`: firmware ESP32 doc flame sensor, DS18B20, dieu khien LED/buzzer va ket noi MQTT.
- `esp32_fire_monitoring/config.example.h`: file mau cau hinh Wi-Fi/MQTT. Copy thanh `config.h` khi chay local.

## Thu vien can cai trong Arduino IDE

- PubSubClient
- ArduinoJson
- OneWire
- DallasTemperature

## Topic MQTT

- Publish telemetry: `home/fire_sensor/1`
- Subscribe dieu khien: `home/fire_control/1`

Payload publish:

```json
{
  "flame": false,
  "temperature": 28.5,
  "alarm": false,
  "timestamp": 12345,
  "device": "ESP32_FireAlarm"
}
```

Lenh dieu khien:

```json
{ "command": "reset" }
{ "buzzer": "on" }
{ "buzzer": "off" }
```
