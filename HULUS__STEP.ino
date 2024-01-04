// pres surucu emre ata
// -*- mode: C++ -*-
// achieved it.
//
// Copyright (C) 2017 Emre Ata


#include <AccelStepper.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C LCD ekranını tanımla

// Define a stepper and the pins it will use
AccelStepper stepper(AccelStepper::FULL2WIRE, 10, 11); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

int buttonState = 0;
int lastButtonState = 0;
const int buttonPin = 2;

void setup()
{  
  lcd.begin(); // LCD ekranını başlat
  lcd.backlight(); // LCD ekranının arka ışığını aç
   pinMode(13, OUTPUT); 
  
    stepper.setMaxSpeed(5000.0);
    stepper.setAcceleration(60000.0);
    pinMode(buttonPin, INPUT);
    Serial.begin(9600);
   // lcd.print("basliyor");
   
}

void loop()
{    
   int sped = analogRead(0);
     sped = map(sped, 0, 1023, 0, 5000);
  int mesafe = analogRead(1);
     mesafe = map(mesafe, 0, 1023, 0, 3000);
  stepper.setMaxSpeed(sped);
  
  lcd.setCursor(0, 0);
  lcd.print("speed=");
    lcd.setCursor(7, 0);
    lcd.print("      ");
    lcd.setCursor(6, 0);
    lcd.print(sped);
  lcd.setCursor(0, 1);
  lcd.print("mesafe=");
    lcd.setCursor(8, 1);
    lcd.print("      ");
    lcd.setCursor(8, 1);
    lcd.print(mesafe);
  
  
  buttonState = digitalRead(buttonPin);
  delay(1);
  
if (buttonState != lastButtonState) {
    // Buton basıldığında
    if (buttonState == HIGH) {
      delay(1);
          digitalWrite(13, LOW);
          stepper.runToNewPosition(mesafe);
          digitalWrite(13, HIGH);
          stepper.setCurrentPosition (0);  // !!!-sıfırlama-!!
           }
    lastButtonState = buttonState; // Bir önceki buton durumunu güncelle
  }


}
