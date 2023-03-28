#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // Set the baud rate for the Serial port
  Serial.begin(9600);

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
  delay(1000);
}

void loop(){
  
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.setCursor(0,0);
  oled.print("Nitrogen:");
  oled.setCursor(5,18);
  oled.print(321);
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
  oled.print(231);
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
  oled.print(231);
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
  oled.print(84);
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
  oled.print(23);
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
  oled.print(97);
  oled.setTextSize(2);
  oled.setCursor(46,18);
  oled.print("%");
  oled.display();
  delay(2000);

  oled.clearDisplay();
  oled.setTextSize(3);
  oled.setTextColor(WHITE);
  oled.setCursor(0,0);
  oled.print("Rice");
  oled.display();
  delay(5000);
  
  oled.clearDisplay();
  oled.setCursor(0,0);
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.print("Press Button for Crop Suggestion");
  oled.display();
}