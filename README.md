# Flame Monitoring System Design

Thiet ke he thong giam sat/phat hien ngon lua dung ESP32, cam bien nhiet do va dashboard web nhan du lieu qua MQTT.

## Cau truc repo

- `web/`: dashboard HTML/CSS/JavaScript, nhan du lieu MQTT va gui lenh dieu khien.
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

Repo nay khong commit credential MQTT that. Truoc khi chay demo, dien broker, username va password HiveMQ trong `web/index.html` o may local. Neu repo public, khong dua credential that vao commit.

## Luu y hien trang

- Co dashboard web va mo phong Proteus, nhung chua thay ma firmware ESP32/Arduino `.ino`, `.cpp` hoac PlatformIO trong thu muc nguon.
- File `idex.html` o thu muc goc ban dau la ban dashboard cu va ten co ve bi go nham; repo nay dung ban moi hon tai `web/index.html`.
- Mot so tai lieu trong `docs/drafts/` la ban nhap/tham khao, khong nhat thiet la ban cuoi.
