//#include <SoftwareSerial.h>
//#include <Wire.h>
//
//// RE and DE Pins set the RS485 module
//// to Receiver or Transmitter mode
//#define RE 15//8
//#define DE 13//7
//
//// Modbus RTU requests for reading NPK values
//const byte nitro[] = {0x01,0x03, 0x00, 0x00, 0x00, 0x03, 0x05, 0xCB};
//const byte phos[] = {0x01,0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
//const byte pota[] = {0x01,0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};
//
//// A variable used to store NPK values
//byte values[11];
//
//// Sets up a new SoftwareSerial object
//// Digital pins 10 and 11 should be used with a Mega or Mega 2560
////SoftwareSerial mod(2, 3);
//SoftwareSerial mod(5, 4);
//
//void setup() {
//  // Set the baud rate for the Serial port
//  Serial.begin(9600);
//
//  // Set the baud rate for the SerialSoftware object
//  mod.begin(9600);
//
//  // Define pin modes for RE and DE
//  pinMode(RE, OUTPUT);
//  pinMode(DE, OUTPUT);
//
//  delay(500);
//}
//
//void loop() {
//  // Read values
//  byte val1,val2,val3;
//  val1 = nitrogen();
//  delay(250);
////  val2 = phosphorous();
////  delay(250);
////  val3 = potassium();
////  delay(250);
//
//  // Print values to the serial monitor
////  Serial.print("Nitrogen: ");
////  Serial.print(val1);
////  Serial.println(" mg/kg");
////  Serial.print("Phosphorous: ");
////  Serial.print(val2);
////  Serial.println(" mg/kg");
////  Serial.print("Potassium: ");
////  Serial.print(val3);
////  Serial.println(" mg/kg");
////
//  delay(2000);
//}
//
//byte nitrogen(){
//  digitalWrite(DE,HIGH);
//  digitalWrite(RE,HIGH);
//  delay(10);
//  if(mod.write(nitro,sizeof(nitro))==8){
//    digitalWrite(DE,LOW);
//    digitalWrite(RE,LOW);
//    for(byte i=0;i<11;i++){
//    //Serial.print(mod.read(),HEX);
//    values[i] = mod.read();
//    Serial.print(values[i],DEC);
//    Serial.print(" ");
//    }
//    Serial.println();
//  }
//  return values[4];
//}
//
//byte phosphorous(){
//  digitalWrite(DE,HIGH);
//  digitalWrite(RE,HIGH);
//  delay(10);
//  if(mod.write(phos,sizeof(phos))==8){
//    digitalWrite(DE,LOW);
//    digitalWrite(RE,LOW);
//    for(byte i=0;i<7;i++){
//    //Serial.print(mod.read(),HEX);
//    values[i] = mod.read();
//    Serial.print(values[i],DEC);
//    Serial.print(" ");
//    }
//    Serial.println();
//  }
//  return values[4];
//}
//
//byte potassium(){
//  digitalWrite(DE,HIGH);
//  digitalWrite(RE,HIGH);
//  delay(10);
//  if(mod.write(pota,sizeof(pota))==8){
//    digitalWrite(DE,LOW);
//    digitalWrite(RE,LOW);
//    for(byte i=0;i<7;i++){
//    //Serial.print(mod.read(),HEX);
//    values[i] = mod.read();
//    Serial.print(values[i],DEC);
//    Serial.print(" ");
//    }
//    Serial.println();
//  }
//  return values[4];
//}


#include <SoftwareSerial.h>
#include <Wire.h>
// RE and DE Pins set the RS485 module
// to Receiver or Transmitter mode
#define RE 15//8
#define DE 13//7

// Modbus RTU requests for reading NPK values
const byte query[] = {0x01,0x03, 0x00, 0x00, 0x00, 0x03, 0x05, 0xCB};

// A variable used to store NPK values
byte response[11];

// Sets up a new SoftwareSerial object
// Digital pins 10 and 11 should be used with a Mega or Mega 2560
//SoftwareSerial mod(2, 3);
SoftwareSerial mod(5, 4);

const int moisture_sensor = A0;  /* Connect Soil moisture analog sensor pin to A0 of NodeMCU */

void setup() {
  // Set the baud rate for the Serial port
  Serial.begin(9600);

  // Set the baud rate for the SerialSoftware object
  mod.begin(9600);

  // Define pin modes for RE and DE
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);

  delay(500);
}

void loop() {

//  byte nitro,phos,potas;
  float moisture_percentage;
  float moisture_read;

  // Read values
//  npk_fun();
  moisture_read=analogRead(moisture_sensor)/1024.00;

//  nitro=response[4];
//  phos=response[6];
//  potas=response[8];

  moisture_percentage = 100.00 - (moisture_read * 100);

  // Print values to the serial monitor
//  Serial.print("Nitrogen: ");
//  Serial.print(nitro);
//  Serial.println(" mg/kg");
//  Serial.print("Phosphorous: ");
//  Serial.print(phos);
//  Serial.println(" mg/kg");
//  Serial.print("Potassium: ");
//  Serial.print(potas);
//  Serial.println(" mg/kg");

  Serial.println(moisture_read);
  Serial.print("Soil Moisture(in Percentage) = ");
  Serial.print(moisture_percentage);
  Serial.println("%");
  delay(2000);
}

void npk_fun(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(query,sizeof(query))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<11;i++){
    response[i] = mod.read();
    Serial.print(response[i],DEC);
    Serial.print(" ");
    }
    Serial.println();
  }
}
//
//#include <DHT.h>      // including the library of DHT11 temperature and humidity sensor
//#define DHTTYPE DHT11   // DHT 11
//
//#define dht_dpin D4
//DHT dht(dht_dpin, DHTTYPE);
//void setup(void)
//{
//  dht.begin();
//  Serial.begin(9600);
//  Serial.println("Humidity and temperature\n\n");
//  delay(700);
//
//}
//void loop() {
//  float h = dht.readHumidity();
//  float t = dht.readTemperature();
//  Serial.print("Current humidity = ");
//  Serial.print(h);
//  Serial.print("%  ");
//  Serial.print("temperature = ");
//  Serial.print(t);
//  Serial.println("C  ");
//  delay(800);
//}
