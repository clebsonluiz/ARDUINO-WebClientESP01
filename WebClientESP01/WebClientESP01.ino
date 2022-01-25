#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h> 

#include "WebSecrets.h"


const char *ssid = WIFI_SSID;
const char *pass = WIFI_PASS;
const char *server_host = HOST_ADDRESS;
const char *api_key_name = API_KEY_NAME;
const char *api_key_value = API_KEY_VALUE;


void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.println();

  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected to: ");
  Serial.print(ssid);
  Serial.print(" IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  WiFiClient client;
  HTTPClient http;

  http.begin(client, server_host); //Only HTTP, Not HTTPS

  //Request Headers
  http.addHeader("Content-Type", "application/json");
  http.addHeader(api_key_name, api_key_value);

  Serial.println("[HTTP RESQUEST] ...");
  // Send Post Request and receive Response http code
  int httpCode = http.POST("{\"Hello\": \"World!\"}");

  Serial.println("[RESPONSE CODE]: " + httpCode);
  
  // If not negative then as made request
  if (httpCode > 0) {

    // if 201 then the response has a payload to read
    if (httpCode == HTTP_CODE_CREATED) {
      const String payload = http.getString();
      Serial.println("Payload:\n");
      Serial.println(payload);
      Serial.println();
    }
  } else {
    Serial.print("[HTTP REQUEST FAILED], [ERROR: ");
    Serial.print(http.errorToString(httpCode).c_str());
    Serial.print("]");
    Serial.println();
  }

  http.end(); // Aways need to end httpclient 
  delay(10000); // New Request in 10 seconds
}
