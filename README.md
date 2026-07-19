# Flame Monitoring System Design

Thiet ke he thong giam sat/phat hien ngon lua dung ESP32, cam bien nhiet do va dashboard web nhan du lieu qua MQTT.

## Cau truc repo

- `web/`: dashboard HTML/CSS/JavaScript, nhan du lieu MQTT va gui lenh dieu khien.
- `firmware/`: ma Arduino/ESP32 trich tu phu luc bao cao va huong dan cau hinh.
- `proteus/`: thu vien Flame Sensor cho Proteus va file mo phong `.DSN/.PWI`.
- `docs/final/`: bao cao, PDF va slide ban nop/cuoi ky.
- `docs/drafts/`: cac ban nhap va tai lieu tham khao lien quan de tai.
- `media/`: anh minh hoa/prototype.

## Dashboard web

File chinh: `web/index.html`

Dashboard dang dung MQTT over WebSocket qua thu vien `mqtt.min.js` tu CDN. Du lieu thiet bi gui len topic:

```json
{
  "temperature": 28.5,
  "flame": false,
  "alarm": false,
  "threshold": 50
}
```

Cac lenh dashboard gui xuong topic dieu khien:

```json
{ "command": "reset" }
{ "buzzer": "on" }
{ "buzzer": "off" }
```

## Luu y bao mat

Source code trong `web/` va `firmware/` khong commit credential Wi-Fi/MQTT that. Truoc khi chay demo, dien cau hinh local theo cac file mau va khong dua credential that vao commit.

## Luu y hien trang

- Ban dau thu muc nguon chi co dashboard web; sau khi doc phu luc Word, source firmware da duoc trich rieng vao `firmware/esp32_fire_monitoring/`.
- Phu luc Word co muc `CODE STM32`, nhung code trong muc do dung thu vien `WiFi.h`, `PubSubClient`, `OneWire`, `DallasTemperature`, nen ve mat ky thuat day la firmware Arduino cho ESP32, khong phai project STM32CubeIDE/HAL.
- File `idex.html` o thu muc goc ban dau la ban dashboard cu va ten co ve bi go nham; repo nay dung ban moi hon tai `web/index.html`.
- Mot so tai lieu trong `docs/drafts/` la ban nhap/tham khao, khong nhat thiet la ban cuoi.
