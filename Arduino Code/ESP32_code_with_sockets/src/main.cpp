#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>

const char* ssid = "Hi";
const char* password = "11882244";
const int port = 8888;

WiFiServer server(port);
WiFiClient client;

void setup() {
  Serial.begin(9600);
  delay(1000);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.begin();
  Serial.println("TCP server started");
}

void loop() {
  if (!client || !client.connected()) {
    client = server.available();
    if (!client) {
      return;
    }
    Serial.println("New client connected");
  }

  if (client.available()) {
    String message = client.readStringUntil('\n');
    message.trim(); 
    if (message == "start") {
      client.println("Action started");
    } else if (message == "stop") {
      client.println("Action stopped");
    } else if (message.length() > 0) {
      Serial.println("Received file content:");
      Serial.println(message);
      client.println("File received");
    } else {
      client.println("Unknown command");
    }
  }
}
