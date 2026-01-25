### ***Reflex test***
This project uses an Arduino circuit and C++ code to implement a reflex test- this test checks how quickly you can click a button after the LED lights up and displays the time on the LCD.

See for yourself: https://www.tinkercad.com/things/0vJMzFowegJ-reflex-test
<hr>

***Circuit Diagram***

<img src="https://csg.us-east-1.prd.tinkercad.com/things/0vJMzFowegJ/t725.png?rev=1769035192078000000&s=&v=1&type=circuits">

<hr>

***Arduino Code:***

```cpp
#include <LiquidCrystal_I2C.h>

// C++ code
//

#define led 7
#define button 9

char bufor[8+1];

LiquidCrystal_I2C lcd(0x26,16,2);

int value;
int time;
bool falstart;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop()
{
  falstart = false;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Wait...");
  time = millis();
  value = random(2,6);
  while(millis() < time + value * 1000){
    if(digitalRead(button) == HIGH){
      delay(20);
      Serial.println("hej");
      falstart = true;
      while(digitalRead(button) == HIGH);
      break;
    }
  }
  
  if(falstart == true){
    lcd.setCursor(0,0);
    lcd.print("Falstart!");
    delay(1000);
  }
  else{
  
  digitalWrite(led, HIGH);
  time = millis();
  while(digitalRead(button) != HIGH);
  
  delay(20);
  time = millis() - time;
  digitalWrite(led, LOW);
  lcd.clear();
  lcd.print("Score: ");
  lcd.print(time);
  
  delay(1000);
  }
  
  
}
