#include <LiquidCrystal_I2C.h>

#define PIN_LED1 5
#define PIN_LED2 4
#define PIN_LED3 3
#define PIN_POT A0
#define Button 6

LiquidCrystal_I2C lcd(0x26,16,2);

const int code[3] = {1, 3, 9};
int value_pot;
int value;
int user_code[3] = {-1,-1,-1};
int i;

unsigned long time_limit;
unsigned long now;
unsigned long start;

void setup() {
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_LED3, OUTPUT);
  pinMode(Button, INPUT);
  
  lcd.init();
  lcd.clear();         
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Guess the code!");
  delay(500);
  lcd.clear();
  Serial.begin(9600);
  
  //all LEDs are on
  digitalWrite(PIN_LED3, HIGH);
  digitalWrite(PIN_LED2, HIGH);
  digitalWrite(PIN_LED1, HIGH);
  
  start = millis();
  time_limit = 10000 + start;

}


void loop() {
  now = millis();
  
  if(now - start > time_limit - 5000){
   //first LED off
   digitalWrite(PIN_LED3, LOW); 
  }
  
  if(now - start > time_limit - 2500){
   //second LED off
   digitalWrite(PIN_LED2, LOW); 
  }
  
  if(now - start > time_limit - 1000){
    //third LED blinks if there's little time left
    if((now - start)/100%2 == 0){
      digitalWrite(PIN_LED1, LOW);
    }
    else{
      digitalWrite(PIN_LED1, HIGH);
    }
  }
  
  if((now - start > time_limit) || user_code[2] != -1){
    lcd.clear();
    lcd.setCursor(0,0);

    if (user_code[0] == code[0] &&
        user_code[1] == code[1] &&
        user_code[2] == code[2]) {
      lcd.print("Congrats!");
    } else {
      lcd.print("Wrong code!");
    }
    while(1);
  }
  value_pot = analogRead(PIN_POT);
  value = value_pot/112; 
  
  lcd.setCursor(4,1);
  if(value == 9){
  lcd.print(" ");
  }
  else{
  lcd.print(value+1);
  }
  lcd.setCursor(7,0);
  lcd.print(value);
  lcd.setCursor(10,1);
   if(value == 0){
  lcd.print(" ");
  }
  else{
  lcd.print(value-1);
  }
  
  if(digitalRead(Button)==HIGH){
    delay(20);
    if(user_code[0] == -1){
      user_code[0] = value;
    }
    else if(user_code[1] == -1){
      user_code[1] = value;
    }
    else if(user_code[2] == -1){
      user_code[2] = value;
    }
    while(digitalRead(Button)==HIGH);
  }
}