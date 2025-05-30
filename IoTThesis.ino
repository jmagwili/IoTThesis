#include <WiFi.h>
#include <HTTPClient.h>

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to WiFi");
  WiFi.begin("Brother-Print", "remember", 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" Connected!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://192.168.0.100:5114/api/iot"); // Replace with your server URL
    http.addHeader("Content-Type", "application/json");

    int deviceID = 2;
    int humidity = 50;
    int temp = 22;

    String jsonPayload = "{";
    jsonPayload += "\"deviceID\": \"" + String(deviceID) + "\", ";  // deviceID should be a string in JSON
    jsonPayload += "\"data\": [";
    jsonPayload += "\"{\\\"temp\\\": " + String(temp) + ", \\\"humidity\\\": " + String(humidity) + "}\"";
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

  delay(1000*60*60);
}