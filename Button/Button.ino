int Signal;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(D0, INPUT_PULLUP);
}

void loop() {

  Signal=digitalRead(D0);
  Serial.println("Digit pin: "+String(Signal));
  Signal=digitalRead(D0);
  delay(1000);
}