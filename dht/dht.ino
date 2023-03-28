#include <DHT.h>
#define DHTPIN D6 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
  Serial.println(F("Measuring Temperature & Humidity.........."));
  delay(1000);
  dht.begin();
} 
void loop(){
float hum = dht.readHumidity();  
float tempC = dht.readTemperature();
float tempF = dht.readTemperature(true);
// To check whether data is collected or not
if (isnan(hum) || isnan(tempC)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
}
float hifrah = dht.computeHeatIndex(tempF, hum);
float hicel = dht.computeHeatIndex(tempC, hum, false);
Serial.print(F(" Humidity: "));
Serial.print(hum);
Serial.print(F("%  Temperature: "));
Serial.print(tempC);
Serial.print(F("°C "));
Serial.print(tempF);
Serial.println(F("°F"));
Serial.print("Temperature Feels like: ");
Serial.print(hicel);
Serial.print(F("°C "));
Serial.print(hifrah);
Serial.println(F("°F"));
delay(3000);
}
