const int sensorPin = A0;
void setup() {
  Serial.begin(9600);
}
void loop() {
  float moisture = analogRead(sensorPin);
  float m = 100 - (moisture/1023)*100;
  float ma = map(moisture,1024,460,0,100);
  Serial.print("Moisture Content: ");
  Serial.print(moisture);
  Serial.print(" ");
  Serial.print(m);
  Serial.print(" ");
  Serial.println(ma);
  delay(1000);
}
