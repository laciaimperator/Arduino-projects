### ***Kitchen Timer v2***
In this project I extended the functionality of the first version with a stop button that stops and resets the selected timer..

See for yourself:https://www.tinkercad.com/things/lVQ1rkv73EM-kitchen-timer-v2
<hr>

***Circuit Diagram***

<img src="https://csg.us-east-1.prd.tinkercad.com/things/lVQ1rkv73EM/t725.png?rev=1767103630959000000&s=&v=1&type=circuits">

<hr>

***Arduino Code:***

```cpp

#include <LiquidCrystal_I2C.h>

#define buzzer 7
#define select 3
#define set 4
#define start 5
#define stop 6

LiquidCrystal_I2C lcd(0x26,16,2);
char bufor[8+1];
int sign_not_select = ' '; //timer has not started and isn't selected
int sign_select = '>'; //timer has not started and is selected
int sign_working = '!'; //timer has started and isn't selected
int sign_stop = '?'; //timer has started but is selected
int which = 0; //selected timer
int pos_x[4] = {0,0,1,1};
int pos_y[4] = {0,8,0,8};
int has_started[4] = {0,0,0,0};
int total_mins[4] = {0,0,0,0}; //the number of minutes
unsigned long start_time[4] = {0,0,0,0}; //millis() at the start of the timer
int cur_mins[4] = {0,0,0,0}; //for printing the remaining minutes
int cur_secs[4] = {0,0,0,0}; //for printing the remaining seconds

int cur_sign[4] = {sign_select, sign_not_select,sign_not_select,sign_not_select}; 

void print_time(int i){
  lcd.setCursor(pos_y[i], pos_x[i]);
  sprintf(bufor, "%c%02d:%02d ", cur_sign[i], cur_mins[i], cur_secs[i]);
  lcd.print(bufor);
}

void buzz(){
 tone(buzzer, 440);
 delay(400);
 tone(buzzer, 440+220);
 delay(400);
 tone(buzzer, 440+440);
 delay(400);
 tone(buzzer, 440+440+220);
 delay(600);
 noTone(buzzer); 
}

void setup()
{
  pinMode(select, INPUT_PULLUP);
  pinMode(set, INPUT_PULLUP);
  pinMode(start, INPUT_PULLUP);
  pinMode(stop, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(" 00:00");
  lcd.setCursor(8,0);
  lcd.print(" 00:00");
  lcd.setCursor(0,1);
  lcd.print(" 00:00");
  lcd.setCursor(8,1);
  lcd.print(" 00:00");
  Serial.begin(9600);
  //select first timer
  print_time(0);
  
}
void loop()
{
  for(int i = 0; i < 4; i++){
      //check if running timers are out of time
      if(has_started[i] == 1){
      	unsigned long duration = total_mins[i] * 60000UL;
      	unsigned long time_passed = millis() - start_time[i];
      	if (time_passed < duration) {
     		unsigned long remaining = duration - time_passed;
      		cur_mins[i] = remaining / 60000;
      		cur_secs[i] = (remaining / 1000) % 60;
      }
      else {
    	cur_mins[i] = 0;
    	cur_secs[i] = 0;
        start_time[i] = 0;
        total_mins[i] = 0;
    	has_started[i] = 0;
        
        buzz();
      }
    }
    
    //update all timer outputs on LCD
  	if(i == which){
    	if(has_started[i] == 1){
        	cur_sign[i] = sign_stop;
        } 
      	else{
        	cur_sign[i] = sign_select;
        }
    }
    else{
    	if(has_started[i] == 1){
        	cur_sign[i] = sign_working;
        } 
      	else{
      		cur_sign[i] = sign_not_select;
        }
   }
   print_time(i);
  }
  
  //select button action on click
  if(digitalRead(select) == LOW){
  delay(20);
  which = (which + 1)%4;
  while(digitalRead(select)==LOW);
  delay(20);
  }
  
  //set button action on click
  if(digitalRead(set) == LOW){
    if(has_started[which] == 0){
  		delay(20);
  		total_mins[which] = total_mins[which] + 1;
      	cur_mins[which] = total_mins[which]; //for printing
    }
  while(digitalRead(set)==LOW);
  delay(20);
  }
  
  //start button action on click
  if(digitalRead(start) == LOW){
      delay(20);
      if(has_started[which] == 0 && cur_mins[which] > 0){
         has_started[which] = 1;
         cur_mins[which] = total_mins[which];
		 cur_secs[which] = 0;
         start_time[which] = millis();
      }
      while(digitalRead(start)==LOW);
      delay(20);
    }
 
  //stop button action on click
  if(digitalRead(stop) == LOW){
    delay(20);
    if(has_started[which] == 1){
     has_started[which] = 0;
     cur_mins[which] = 0;
     cur_secs[which] = 0;
     start_time[which] = 0;
     total_mins[which] = 0;
    }
    while(digitalRead(stop)==LOW);
    delay(20);
  }

  
}
  

  
}

```
