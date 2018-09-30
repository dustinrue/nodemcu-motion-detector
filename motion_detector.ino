
// HC-SR501 Pir
#define MQTT_TOPIC "home/motion/garage"
#define MQTT_CLIENT "ESP8266 Motion Sensor 2"

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "wifi.h"

const char* ssid     = SSID;
const char* password = PASS;
const char* mqtt     = MQTT;


WiFiClient espClient;
PubSubClient client(espClient);

int Sensor = 13;
int motion_detected = 0;

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(MQTT_CLIENT)) {
      Serial.println("connected");
    } 
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(Sensor, INPUT);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());

  client.setServer(mqtt, 1883);
  reconnect();

}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  long state = digitalRead(Sensor);
  if (state == HIGH) {
    Serial.println("motion");
    
    if (motion_detected != 1) {
      motion_detected = 1;
      client.publish(MQTT_TOPIC, "1");
    }
  }
  else {
    Serial.println("no motion");
   
    if (motion_detected != 0) {
      motion_detected = 0;
      client.publish(MQTT_TOPIC, "0");
    }
    
  }
  delay(250);
}
