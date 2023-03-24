#include <SoftwareSerial.h>
#include <Wire.h>

// RE and DE Pins set the RS485 module
// to Receiver or Transmitter mode
#define RE 15 //D8
#define DE 13 //D7

// Modbus RTU requests for reading NPK values
const byte query[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x03, 0x05, 0xCB};

// A variable used to store NPK values
byte response[11];

// Sets up a new SoftwareSerial object
SoftwareSerial mod(0, 2); //(RO,DI)-(D3,D4)

void setup() {
  // Set the baud rate for the Serial port
  Serial.begin(9600);
  
  
  // Set the baud rate for the SerialSoftware object
  mod.begin(9600);

  // Define pin modes for RE and DE
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
  delay(1000);
}

void loop() {

  byte nitro, phos, potas;

  NPKFunc();

  nitro = response[4];
  phos = response[6];
  potas = response[8];
  delay(4000);
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
      Serial.print(response[i]);
      Serial.print(" ");
    }
    Serial.println();
  }
}
