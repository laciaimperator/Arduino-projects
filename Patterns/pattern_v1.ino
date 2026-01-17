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

int counter = 0;
int i;
int j;
int a;
int b;



void setup()
{
  lcd.init();
  lcd.backlight();

  // upload custom characters to LCD memory
  lcd.createChar(0, customChar);
  lcd.createChar(1, customChar1);
  
}

void loop()
{
  while(counter <= 20){
    if(counter%2 == 0){
      	a = 0;
      	b = 1;
    }
    else{
      a = 1;
      b = 0;
    }
    counter = counter + 1;
    delay(100);
  		for(i=0; i<2; i++){
          if(i==0){
    		for(j=0; j<16;j++){
        		lcd.setCursor(j,i);
        		if(j%2==0){
  		  			lcd.write(a);
        		}
        		else{
          			lcd.write(b);
        		}
    		}
          }
          else{
          for(j=16; j>=0;j--){
        		lcd.setCursor(j,i);
        		if(j%2==0){
  		  			lcd.write(a);
        		}
        		else{
          			lcd.write(b);
        		}
    		}
          }
  		}
    }
}