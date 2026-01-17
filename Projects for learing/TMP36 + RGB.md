### ***TMP36 + RGB***
In this project, I learned how to use a TMP36 temperature sensor and an RGB LED to create a circuit that reads the current temperature, displays it on an LCD screen, and depending on whether the temperature is high or low, the appropriate color lights up on the LED.

See for yourself: https://www.tinkercad.com/things/cJ1uQosuc9H-temperature-lcd-rgb
<hr>

***Circuit Diagram***

<img src="https://csg.us-east-1.prd.tinkercad.com/things/cJ1uQosuc9H/t725.png?rev=1768155326187000000&s=&v=1&type=circuits">

<hr>

***Arduino Code:***

```cpp
#include <LiquidCrystal_I2C.h>

#define RED 12
#define GREEN 13
#define BLUE 11
#define TMP A0

// C++ code
//
float voltage;
float temp;

LiquidCrystal_I2C lcd(0x26, 16, 2);


void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);

  lcd.init();
  lcd.clear();
  lcd.backlight();
  
}

void loop()
{
  int raw = analogRead(TMP);
  voltage = raw * (5.0 / 1023.0);
  temp = (voltage - 0.5) * 100.0;
  
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  lcd.setCursor(0,1);
  lcd.print(temp);
  lcd.print(" C");
  
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  
  if(temp > 90){
  digitalWrite(RED, HIGH);
  }
  else if(temp > 0){
  digitalWrite(GREEN, HIGH);
  }
  else{
  digitalWrite(BLUE, HIGH);
  }
  
  delay(1000);
}

//when using DS18B20
//import libraries: Wire, OneWire, DallasTemperature
//before setup:
//OneWire oneWire(TMP);  
//TMP is your digital PIN
//DallasTemperature sensors(&oneWire);
//in setup:
//sensors.begin();
//in loop:
//sensors.requestTemperatures();
//temp = sensors.getTempCByIndex(0);
