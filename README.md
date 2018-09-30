# NodeMCU ESP8266 Based Motion Sensor

Simple motion sensor setup that publishes status to an MQTT topic. Uses HC-SR501 PIR sensor.

Connect sensor to power +/- and data pin to pin 13 of the NodeMCU.

## WiFi Configuration

You must create a file called wifi.h with the following:

```
#define SSID "ssid of your wifi network";
#define PASS "password for wifi network";
```

## Serial

Please note that serial connection speed should be set to 115200. 
