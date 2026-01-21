### ***Game***
This project uses an Arduino circuit and C++ code to implement a game. A rock is coming your way, and you have to jump out of its way. 
You press a button, and your character changes lanes to avoid the obstacle.

See for yourself: https://www.tinkercad.com/things/0NDvn4kNJ2B-game
<hr>

***Circuit Diagram***

<img src="https://csg.us-east-1.prd.tinkercad.com/things/0NDvn4kNJ2B/t725.png?rev=1768673900504000000&s=&v=1&type=circuits">

<hr>

***Arduino Code:***

```cpp

#include <LiquidCrystal_I2C.h>
#define Button 2

LiquidCrystal_I2C lcd(0x26,16,2);

byte character[] = {
  B01110,
  B01110,
  B00100,
  B11111,
  B00100,
  B01010,
  B10001,
  B00010
};

byte stone[] = {
  B00000,
  B00000,
  B01100,
  B10010,
  B10010,
  B01100,
  B00000,
  B00000
};

int c_pos[2] = {0,1};
int s_pos[2] = {15,0};

void setup()
{
  Serial.begin(9600);
  pinMode(Button, INPUT);
  lcd.init();
  lcd.clear();         
  lcd.backlight();

  lcd.createChar(0, character);
  lcd.createChar(1, stone);
  lcd.setCursor(0,1);
  lcd.write(0);
}
unsigned long time = 0;
const int speed = 100;

void loop()
{
  
if (millis() - time >= speed) {
  time = millis();
  lcd.setCursor(s_pos[0], s_pos[1]);
  lcd.print(" ");
  s_pos[0]--;
  if (s_pos[0] < 0) {
    s_pos[1] = random(0,2);
    s_pos[0] = 15;
  }
  lcd.setCursor(s_pos[0], s_pos[1]);
  lcd.write(1);
}
  
  //moving character
  if(digitalRead(Button) == HIGH){
    delay(20);
    if(c_pos[1] == 0){
    lcd.setCursor(c_pos[0],c_pos[1]);
    lcd.print(" ");
    c_pos[1]=1;
    lcd.setCursor(c_pos[0],c_pos[1]);
    lcd.write(0);
    }
    else if(c_pos[1] == 1){
    lcd.setCursor(c_pos[0],c_pos[1]);
    lcd.print(" ");
    c_pos[1]=0;
    lcd.setCursor(c_pos[0],c_pos[1]);
    lcd.write(0);
    }
    while(digitalRead(Button) == HIGH);
  }
  
  if(c_pos[0] == s_pos[0] && c_pos[1] == s_pos[1]){
  	lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("GAME OVER!!!");
    while(1);
  }
  
  }

