#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>
IRsend irsend(3);
LiquidCrystal_I2C lcd(0x27, 20, 4);
int cursorPointer = 0;
DHT HT(2, DHT11);
void setup() {
  // put your setup code here, to run once:
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  Serial.begin(9600);
  HT.begin();
  delay(1000);
}
void printText(String message) {
  lcd.setCursor(0 , cursorPointer);
  cursorPointer += 1;
  lcd.print(message);
}
void printLCD(float humid, float tempC) {
  String text1 = "Humid: " + String(humid);
  printText(text1);
  String text2 = "Temp: " + String(tempC);
  printText(text2);
}
void loop() {
  // put your main code here, to run repeatedly:
  float humid = HT.readHumidity();
  float tempC = HT.readTemperature();

  Serial.print("Humidity:");
  Serial.print(humid, 0);
  Serial.println("%");
  Serial.print(" Temperature:");
  Serial.print(tempC, 1);
  Serial.println("‎°C ~ ");

  printLCD(humid, tempC );

  delay(500);
  cursorPointer = 0;
  lcd.clear();
  if (tempC >= 35) {
    irsend.sendRC5(0x0, 8); delay(200);
  } else if (tempC >= 33 && tempC < 35) {
    irsend.sendRC5(0x1, 8); delay(200);
  } else {
    irsend.sendRC5(0x2, 8); delay(200);
  }

}
