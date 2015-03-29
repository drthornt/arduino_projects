#include <LiquidCrystal.h>
#include <Wire.h>
#include "HTU21D.h"

HTU21D myHumidity;

LiquidCrystal lcd(12,11,5,4,3,2);

void setup() {
  lcd.begin(16, 2 );
  lcd.print("Hello world");

  myHumidity.begin();
  
}

void loop() {
  delay(1000);
  lcd.setCursor(0, 1);

  float humd = myHumidity.readHumidity();
  float temp = myHumidity.readTemperature();
  
  lcd.print("T:");
  lcd.print(temp);
  lcd.print(" H: ");
  lcd.print(humd);
  delay(2000);
  

}
