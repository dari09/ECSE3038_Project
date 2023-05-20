#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "env.h"

const char* putEndpoint = API_URL_PUT;
const char* getEndpoint = API_URL_GET;

const int fanPin = 22;
const int lightPin = 23;

float generateRandomFloat(float min, float max)
{
    float scale = rand() / (float) RAND_MAX;
    return min + scale * (max - min);
}

void setup() {
  Serial.begin(9600);
  pinMode(fanPin, OUTPUT);
  pinMode(lightPin, OUTPUT);

  WiFi.begin(WIFI_USER, WIFI_PASS);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
  Serial.print("Local IP address: ");
  Serial.println(WiFi.localIP());
}

void switchLightAndFan(bool lightState, bool fanState)
{
  digitalWrite(fanPin, fanState);
  digitalWrite(lightPin, lightState);
  
  Serial.println("Light and Fan Switched Successfully");
}

void sendPutRequest(float temperature)
{
  HTTPClient http;
  
  http.begin(putEndpoint);
  http.addHeader("Content-Type", "application/json");

  StaticJsonDocument<1024> putDoc;
  putDoc["temperature"] = temperature;

  String httpRequestData;
  serializeJson(putDoc, httpRequestData);

  int putResponseCode = http.PUT(httpRequestData);

  if (putResponseCode > 0) {
    Serial.print("PUT Response Code: ");
    Serial.println(putResponseCode);
  } else {
    Serial.print("PUT Request Failed. Error Code: ");
    Serial.println(putResponseCode);
  }

  http.end();
}

void handleGetResponse(String& response)
{
  StaticJsonDocument<1024> doc;
  DeserializationError error = deserializeJson(doc, response);

  if (error) {
    Serial.print("Failed to parse JSON response. Error: ");
    Serial.println(error.c_str());
    return;
  }

  bool lightState = doc["light"];
  bool fanState = doc["fan"];

  Serial.println("Light State: " + String(lightState));
  Serial.println("Fan State: " + String(fanState));

  switchLightAndFan(lightState, fanState);
}

void sendGetRequest()
{
  HTTPClient http;

  http.begin(getEndpoint);

  int getResponseCode = http.GET();

  if (getResponseCode > 0) {
    Serial.print("GET Response Code: ");
    Serial.println(getResponseCode);

    String response = http.getString();
    handleGetResponse(response);
  } else {
    Serial.print("GET Request Failed. Error Code: ");
    Serial.println(getResponseCode);
  }

  http.end();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    float temperature = generateRandomFloat(21.0, 33.0);
    sendPutRequest(temperature);
    
    sendGetRequest();
    
    delay(1000);
  } else {
    Serial.println("Not Connected to WiFi");
  }
}
