#include <SoftwareSerial.h>
#include <Wire.h>
#include <DHT.h>
#include "ESP8266WiFi.h"
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char* WIFINAME = "Galaxy A30s";
const char* PASS = "fezk2045";

//int led = D0;
WiFiServer server(80);

// RE and DE Pins set the RS485 module
// to Receiver or Transmitter mode
#define RE 15 //D8
#define DE 13 //D7

#define DHTPIN 12 // D6
#define DHTTYPE DHT11

bool Status = false;

// Connect Soil moisture analog sensor pin to A0 of NodeMCU
const int moisture_sensor = A0;

// Modbus RTU requests for reading NPK values
const byte query[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x03, 0x05, 0xCB};

// A variable used to store NPK values
byte response[11];

// Initializing DHT sensor with dht pin
DHT dht(DHTPIN, DHTTYPE);

// Sets up a new SoftwareSerial object
SoftwareSerial mod(0, 2); //(RO,DI)-(D3,D4)

void setup() {
  // Set the baud rate for the Serial port
  Serial.begin(9600);
  Serial.print("Connecting To ");
  Serial.print(WIFINAME);
  WiFi.begin(WIFINAME, PASS);

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  delay(1000);
  oled.clearDisplay();
  oled.setCursor(0,0);
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.print("Press Button for Crop Suggestion");
  oled.display();

  // Set the baud rate for the SerialSoftware object
  mod.begin(9600);

  // Initializing DHT Sensor
  dht.begin();

  pinMode(D0, INPUT_PULLUP);

  // Define pin modes for RE and DE
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("WiFi Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(1000);
}

void loop() {

  byte nitro, phos, potas;
  float moisture_read;
  float moisture_int;
  float moisture_percentage;

  NPKFunc();
  moisture_int = analogRead(moisture_sensor);
  moisture_percentage = map(moisture_int,0,1023,75,250);

  nitro = response[4];
  phos = response[6];
  potas = response[8];

  float hum = dht.readHumidity();
  float tempC = dht.readTemperature();

  int Signal=digitalRead(D0);
  Serial.println("Digit pin:"+String(Signal));
  if (Signal==1)
  {
    Serial.println("Button Pressed");
    if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
      WiFiClient client;
      HTTPClient http;
      String query_api="http://192.168.67.43:8000/api/data/?n="+String(nitro)+"&p="+String(phos)+"&k="+String(potas)+"&t="+String(tempC)+"&h="+String(hum)+"&rain="+String(moisture_percentage);
      http.begin(client,query_api); //Specify the URL
      int httpCode = http.GET();                                        //Make the request

      if (httpCode > 0) { //Check for the returning code

        String payload = http.getString();
        Serial.print("Suitable Crop to grow: ");
        Serial.println(payload.substring(2,payload.length()-2));
        display_serial(nitro, phos, potas, hum, tempC, moisture_percentage);
        display_oled(nitro, phos, potas, hum, tempC, moisture_percentage,payload.substring(2,payload.length()-2));
        
      }
      else {
        Serial.println("Error on HTTP request");
      }
      http.end(); //Free the resources
    }
    else{
      Serial.println("Wifi Not Connected");
    }
    Signal=0;
  }
  else{
    Serial.println("Button Not Pressed");
  }
  delay(1000);
}

void NPKFunc() {

  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(10);
  if (mod.write(query, sizeof(query)) == 8) {
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);
    for (byte i = 0; i < 11; i++) {
      response[i] = mod.read();
    }
  }
}
void display_serial(byte nitro , byte phos, byte potas, float hum, float tempC, float moisture_percentage){
  Serial.print(F("Nitrogen: "));
  Serial.print(nitro);
  Serial.println(F(" mg/Kg"));
  Serial.print(F("Phosphorous: "));
  Serial.print(phos);
  Serial.println(F(" mg/Kg"));
  Serial.print(F("Potassium: "));
  Serial.print(potas);
  Serial.println(F("mg/Kg"));

  Serial.print(F("Soil Moisture(in Percentage) = "));
  Serial.print(moisture_percentage);
  Serial.println(F("%"));

  Serial.print(F("Humidity: "));
  Serial.print(hum);
  Serial.print(F("%  Temperature: "));
  Serial.print(tempC);
  Serial.println(F("°C "));
}

void display_oled(byte nitro , byte phos, byte potas, float hum, float tempC, float moisture_percentage, String crop){
  
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.setCursor(0,0);
  oled.print("Nitrogen:");
  oled.setCursor(5,18);
  oled.print(nitro);
  oled.setTextSize(1);
  oled.setCursor(43,18);
  oled.print("mg/Kg");
  oled.display();
  delay(2000);

  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.setCursor(0,0);
  oled.print("Phosphorus:");
  oled.setCursor(5,18);
  oled.print(phos);
  oled.setTextSize(1);
  oled.setCursor(43,18);
  oled.print("mg/Kg");
  oled.display();
  delay(2000);

  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.setCursor(0,0);
  oled.print("Potassium:");
  oled.setCursor(5,18);
  oled.print(potas);
  oled.setTextSize(1);
  oled.setCursor(43,18);
  oled.print("mg/Kg");
  oled.display();
  delay(2000);

  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.setCursor(0,0);
  oled.print("Moisture:");
  oled.setCursor(6,18);
  oled.print(moisture_percentage);
  oled.setTextSize(2);
  oled.setCursor(46,18);
  oled.print("%");
  oled.display();
  delay(2000);

  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.setCursor(0,0);
  oled.print("Temp:");
  oled.setCursor(6,18);
  oled.print(tempC);
  oled.setTextSize(1);
  oled.setCursor(46,18);
  oled.print("°C");
  oled.display();
  delay(2000);

  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.setCursor(0,0);
  oled.print("Humidity:");
  oled.setCursor(6,18);
  oled.print(hum);
  oled.setTextSize(2);
  oled.setCursor(46,18);
  oled.print("%");
  oled.display();
  delay(2000);

  oled.clearDisplay();
  oled.setTextSize(3);
  oled.setTextColor(WHITE);
  oled.setCursor(0,0);
  oled.print(crop);
  oled.display();
  delay(5000);
  
  oled.clearDisplay();
  oled.setCursor(0,0);
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.print("Press Button for Crop Suggestion");
  oled.display();
}
