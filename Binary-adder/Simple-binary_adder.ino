#include <LiquidCrystal_I2C.h>
#define clockPin 9
#define latchPin 10
#define dataPin 11
#define addPin 7
#define subPin 6

LiquidCrystal_I2C lcd(0x26,16,2);

int value = 0;

void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(addPin, INPUT);
  pinMode(subPin, INPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.clear();         
  lcd.backlight();

}

void loop()
{
  
  if (digitalRead(addPin) == HIGH){
    delay(20);
  	value ++;
    if (value > 255) value = 255;
    while(digitalRead(addPin) == HIGH);
    delay(2);
  }
  else if (digitalRead(subPin) == HIGH){
    delay(20);
  	value --;
    if (value < 0) value = 0;
    while(digitalRead(subPin) == HIGH);
    delay(2);
  }
  
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, value);
  digitalWrite(latchPin, HIGH); 
  lcd.clear();
  lcd.print(value);
  Serial.println(value);
}
