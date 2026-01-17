#include <LiquidCrystal_I2C.h>

#define clockPin 9
#define latchPin 10
#define dataPin 11
#define button 7

LiquidCrystal_I2C lcd(0x26,16,2);

byte leds = 0;
int val=0;

void setup()
{
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
}

void loop()
{
  leds = 0;
  
  if(digitalRead(button) == HIGH){
    val = random(1,7);
    Serial.println(val);
  }

  for(int i =0; i < val; i++){
    bitSet(leds, i);
  }
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, 'MSFIRST', leds);
  digitalWrite(latchPin, HIGH);
  lcd.setCursor(0,0);
  lcd.print("Value on dice:");
  lcd.setCursor(0,1);
  lcd.print(val);
  
}