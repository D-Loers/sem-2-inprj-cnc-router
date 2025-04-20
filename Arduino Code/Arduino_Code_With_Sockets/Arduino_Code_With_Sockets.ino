#include <DHT20.h>
#include <Wire.h>
#include <WiFi.h>

DHT20 DHT

// WiFi parameters
const char* ssid = "";
const char* password = "";
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Start the server
  server.begin();
  Wire.begin();
  DHT.begin();
  delay(2000);
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client connected");
    
    sendSensorData(client);
    
    delay(5000);

    Serial.println("closing connection...");
    client.stop();
  }

  if (millis() - DHT.lastRead() >= 1000) {
    DHT.read();
    display();
  }
}
