#include "ESP8266WiFi.h"
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
const char* WIFINAME = "RPN2";
const char* PASS = "rpn2@123";
//int led = D0;
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.print("Connecting To ");
  Serial.println(WIFINAME);


  WiFi.begin(WIFINAME, PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    WiFiClient client;
    HTTPClient http;

    http.begin(client, "http://192.168.0.148:8000/api/data/"); //Specify the URL
    int httpCode = http.GET();                                        //Make the request

    if (httpCode > 0) { //Check for the returning code

      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);
    }

    else {
      Serial.println("Error on HTTP request");
    }

    http.end(); //Free the resources
  }

    delay(5000);
}
