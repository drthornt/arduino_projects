#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

void setup() {
  lcd.begin(16, 2 );
  lcd.print("Hello world");
}

void loop() {
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print(millis()/100);
}
