/*  
 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
  */

#include <LiquidCrystal_1602_RUS.h>

//LiquidCrystal_1602_RUS lcd(12, 11, 5, 4, 3, 2);
LiquidCrystal_1602_RUS lcd(8, 9, 4, 5, 6, 7 );//For LCD Keypad Shield

void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(1, 0);
  lcd.print(L"Можно печатать");
  lcd.setCursor(3, 1);
  lcd.print(L"на русском");
}

void loop()
{
}
