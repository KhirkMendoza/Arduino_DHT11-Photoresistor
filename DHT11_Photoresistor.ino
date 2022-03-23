#include <dht.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

dht DHT;//create a variable type of dht

#define DHT11_PIN 7

const int ledPin = 8;
const int ldrPin = A0;
const int buttonPin = 6;
int buttonClick;
int count;

unsigned long keypressMillis = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
  pinMode(buttonPin, INPUT);

}

void loop() {
  unsigned long currentMillis = millis();

  buttonClick = digitalRead(buttonPin);
  if (buttonClick == HIGH) {
    delay(50);
    buttonClick = digitalRead(buttonPin);
    if (buttonClick == LOW) {
      delay(10);
      count++;
    }
  }
  if (count == 1) {
    const long interval = 500;
    if ((currentMillis - keypressMillis) >= interval) {

      int ldrStatus = analogRead(ldrPin);

      if (ldrStatus >= 300) {
        lcd.clear();
        digitalWrite(ledPin, HIGH);
        lcd.setCursor(0, 0);
        lcd.print("LED Status:  ON");
        lcd.setCursor(0, 1);
        lcd.print("Sensor Val:");
        lcd.setCursor(12, 1);
        lcd.print(ldrStatus);
        Serial.println(ldrStatus);

      }

      else {
        lcd.clear();
        digitalWrite(ledPin, LOW);
        lcd.setCursor(0, 0);
        lcd.print("LED Status: OFF");
        lcd.setCursor(0, 1);
        lcd.print("Sensor Val:");
        lcd.setCursor(12, 1);
        lcd.print(ldrStatus);

      }
      keypressMillis = currentMillis;
    }
  }
  else if (count == 2) {
    const long interval = 1200;
    if ((currentMillis - keypressMillis) >= interval) {

      int chk = DHT.read11(DHT11_PIN);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp: ");
      lcd.print(DHT.temperature);
      lcd.print((char)223);
      lcd.print("C");
      lcd.setCursor(0, 1);
      lcd.print("Humidity: ");
      lcd.print(DHT.humidity);
      lcd.print("%");
      keypressMillis = currentMillis;
    }
  }
  else {
    const long interval = 500;
    if ((currentMillis - keypressMillis) >= interval) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Photoresistor &");
      lcd.setCursor(5, 1);
      lcd.print("DHT11");
      count = 0;
      keypressMillis = currentMillis;
    }
  }
}
