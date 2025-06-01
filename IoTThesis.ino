#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

const String API = "http://192.168.0.104:5114";
const int deviceID = 1;

void setup() {
  // Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  
  Serial.begin(115200);
  Serial.print("Connecting to WiFi");
  WiFi.begin("Brother-Print", "remember", 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" Connected!");

  dht.begin();
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(API + "/api/iot"); // Replace with your server URL
    http.addHeader("Content-Type", "application/json");

    int deviceID = 2;

    String jsonPayload = "{";
    jsonPayload += "\"deviceID\": \"" + String(deviceID) + "\", ";  // deviceID should be a string in JSON
    jsonPayload += "\"data\": [";
    jsonPayload += "\"{\\\"temp\\\": " + String(t) + ", \\\"humidity\\\": " + String(h) + "}\"";
    jsonPayload += "]";
    jsonPayload += "}";

    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode > 0) {
      Serial.println("HTTP Response code: " + String(httpResponseCode));
      Serial.println("Response: " + http.getString());
    } else {
      Serial.println("Error on sending POST: " + String(httpResponseCode));
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }

  delay(1000*60*10);
}