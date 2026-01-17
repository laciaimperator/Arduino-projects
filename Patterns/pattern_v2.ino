#include <LiquidCrystal_I2C.h>

// C++ code
//

LiquidCrystal_I2C lcd(0x26,16,2);

byte customChar[] = {
  B00000,
  B00000,
  B01010,
  B10101,
  B01010,
  B00100,
  B00000,
  B00000
};

byte customChar1[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00100,
  B00000,
  B00000,
  B00000
};

byte customChar2[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

int counter = 0;
int j;


void setup()
{
  lcd.init();
  lcd.backlight();

  lcd.createChar(0, customChar);
  lcd.createChar(1, customChar1);
  lcd.createChar(2, customChar2);
  
}

void loop()
{
lcd.setCursor(0,0);
lcd.write(0);
  
  for(j=1;j<16;j++){
      lcd.setCursor(j,0);
      lcd.write(0);
      lcd.setCursor(j-1,0);
      lcd.write(counter%2+1);
      delay(200);
  }
  
  lcd.setCursor(15,0);
  lcd.write(counter%2+1);
  
  for(j=16;j>=0;j--){
    lcd.setCursor(j,1);
    lcd.write(0);
    lcd.setCursor(j+1,1);
    lcd.write(counter%2+1);
    delay(200);
  }
  lcd.setCursor(0,1);
  lcd.write(counter%2+1);
  
  counter += 1;
}