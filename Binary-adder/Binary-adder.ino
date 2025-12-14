#include <LiquidCrystal_I2C.h>
#define clockPin 9
#define latchPin 10
#define dataPin 11
#define rndPin 7
#define checkPin 6
#define potencjometrPin A3

LiquidCrystal_I2C lcd(0x26,16,2);

int value = 0; // od 0 do 255
int val_pot = 0;
bool read_pot = true;

void output(String text, int number){
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(text);
  	lcd.print(": ");
	lcd.print(number);

}

void rejestr(int number) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, number);
    digitalWrite(latchPin, HIGH);
}

void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(rndPin, INPUT);
  pinMode(checkPin, INPUT);
  
  Serial.begin(9600);
  lcd.init();       
  lcd.backlight();

}

void loop()
{
  if(digitalRead(checkPin) == HIGH){
  read_pot = true;
  delay(200);
  }
  
  if(digitalRead(rndPin) == HIGH){
    read_pot = false;
  	value = random(0,129);
	output("Random value", value);
    rejestr(value);
    Serial.println(value);
    
    while(digitalRead(rndPin) == HIGH);
    delay(200);
  }
  
   if(read_pot == true){
    val_pot = analogRead(potencjometrPin);
    value = val_pot /8;
    output("Value", value);
    rejestr(value);
    delay(200); 
    }
}