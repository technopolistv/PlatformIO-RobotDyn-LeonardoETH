## How to use RobotDyn Arduino Leonardo Ethernet W5500 with PlatformIO

![RobotDyn Arduino Leonardo Ethernet W5500](/robotdyn-leonardo-ethernet-w5500-poe-bg.jpg)

Here is a working example for _RobotDyn Arduino Leonardo ETH_ with PlatformIO.

## How it works

TL;DR Pull `RST` pin 11 `HIGH` before `Ethernet.begin()`. Optionally pull `SS` pin 10 `LOW` before `Ethernet.begin()` and `HIGH` afterwards.

```
#define SS  10  // W5500 CS
#define RST 11  // W5500 RST

pinMode(RST, OUTPUT);
digitalWrite(RST, HIGH);

Ethernet.begin(mac, ip);
```
You can assign a static IP address and connect to it via `netcat` or other UDP client on port `8888`.

```
$ echo -n "0123456789 abcdef ABCDEF" | nc -u 192.168.23.23 8888
```

Every received UDP packet will be acknowledged with __uptime__ of the device in milliseconds and __echo__ of the received packet.

✍️ Blog: https://www.technopolis.tv/PlatformIO-How-to-use-RobotDyn-Arduino-Leonard-Ethernet-W5500/