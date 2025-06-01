#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

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

   // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  // if (WiFi.status() == WL_CONNECTED) {
  //   HTTPClient http;
  //   http.begin("http://192.168.0.100:5114/api/iot"); // Replace with your server URL
  //   http.addHeader("Content-Type", "application/json");

  //   int deviceID = 2;
  //   int humidity = 50;
  //   int temp = 22;

  //   String jsonPayload = "{";
  //   jsonPayload += "\"deviceID\": \"" + String(deviceID) + "\", ";  // deviceID should be a string in JSON
  //   jsonPayload += "\"data\": [";
  //   jsonPayload += "\"{\\\"temp\\\": " + String(temp) + ", \\\"humidity\\\": " + String(humidity) + "}\"";
  //   jsonPayload += "]";
  //   jsonPayload += "}";

  //   int httpResponseCode = http.POST(jsonPayload);

  //   if (httpResponseCode > 0) {
  //     Serial.println("HTTP Response code: " + String(httpResponseCode));
  //     Serial.println("Response: " + http.getString());
  //   } else {
  //     Serial.println("Error on sending POST: " + String(httpResponseCode));
  //   }

  //   http.end();
  // } else {
  //   Serial.println("WiFi Disconnected");
  // }

  // delay(1000*60*60);
}