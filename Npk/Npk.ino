#include <SoftwareSerial.h>
#include <Wire.h>
#include <DHT.h>

// RE and DE Pins set the RS485 module
// to Receiver or Transmitter mode
#define RE 15//8
#define DE 13//7

#define DHTPIN 14
#define DHTTYPE DHT11

// Initializing DHT sensor with dht pin
DHT dht(DHTPIN, DHTTYPE);

// Modbus RTU requests for reading NPK values
const byte query[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x03, 0x05, 0xCB};

// A variable used to store NPK values
byte response[11];

// Sets up a new SoftwareSerial object
SoftwareSerial mod(5, 4);

// Connect Soil moisture analog sensor pin to A0 of NodeMCU 
const int moisture_sensor = A0;

void setup() {
  // Set the baud rate for the Serial port
  Serial.begin(9600);

  // Set the baud rate for the SerialSoftware object
  mod.begin(9600);

  // Initializing DHT Sensor
  dht.begin();

  // Define pin modes for RE and DE
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
  
  delay(1000);
}

void loop() {
  
  byte nitro, phos, potas;
  float moisture_read;
  float moisture_int;
  float moisture_percentage;

  NPKFunc();
  moisture_read = analogRead(moisture_sensor);
  moisture_int = moisture_read;
  moisture_percentage = 100.00 - (moisture_int * 100);
  
  nitro = response[4];
  phos = response[6];
  potas = response[8];

  float hum = dht.readHumidity();
  float tempC = dht.readTemperature();

  // Print values to the serial monitor
  Serial.print(F("Nitrogen: "));
  Serial.print(nitro);
  Serial.println(F(" mg/Kg"));
  Serial.print(F("Phosphorous: "));
  Serial.print(phos);
  Serial.println(F(" mg/Kg"));
  Serial.print(F("Potassium: "));
  Serial.print(potas);
  Serial.println(F("mg/Kg");

  Serial.print(F("Soil Moisture(in Percentage) = "));
  Serial.print(moisture_percentage);
  Serial.println(F("%"));

  Serial.print(F(" Humidity: "));
  Serial.print(hum);
  Serial.print(F("%  Temperature: "));
  Serial.print(tempC);
  Serial.print(F("°C "));
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
      Serial.print(response[i], DEC);
      Serial.print(" ");
    }
    Serial.println();
  }
}
