#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <HTTPClient.h>

// WiFi credentials
const char* wifiSSID = "Tarigeng";
const char* wifiPassword = "17022004";

// Server details
const char* apiEndpoint = "http://192.168.1.37:5000/data";

// Sensor pin
int airSensorPin = 34;

// Function to read air quality data
int readAirQuality() {
  int airQualityValue = analogRead(airSensorPin);
  Serial.print("Air Quality: ");
  Serial.println(airQualityValue);
  delay(300);  // Delay to stabilize sensor
  return airQualityValue;
}

// Function to send sensor data to the server
void sendSensorData(){
  WiFiClient wifiClient;
  HTTPClient httpClient;

  int airQuality = readAirQuality();
  httpClient.begin(wifiClient, apiEndpoint);
  httpClient.addHeader("Content-Type", "application/json");

  // Create JSON payload
  String jsonPayload = "{";
  jsonPayload += "\\"Air Quality\\": " + String(airQuality) + ", ";
  jsonPayload += "\\"temperature\\": " + String(airQuality) + ", ";
  jsonPayload += "\\"humidity\\": " + String(airQuality) + "}";
  
  // Send POST request
  int httpResponse = httpClient.POST(jsonPayload);

  Serial.print("HTTP Response code: ");
  Serial.println(httpResponse);
  Serial.println(jsonPayload);

  httpClient.end();

  delay(5000);
}

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA); // Set WiFi mode to station
  WiFi.begin(wifiSSID, wifiPassword);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Print success message
  Serial.println("");
  Serial.println("WiFi connected!");
}

void loop() {
  sendSensorData();
}
