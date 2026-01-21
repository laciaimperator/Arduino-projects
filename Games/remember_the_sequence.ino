// C++ code
//

#define LED1 5
#define LED2 6
#define LED3 7
#define B1 4
#define B2 3
#define B3 2

int which_led;
int seq[10] = {0,0,0,0,0,0,0,0,0,0};
int counter;


int get_button() {
  while(digitalRead(B1) == HIGH || digitalRead(B2) == HIGH || digitalRead(B3) == HIGH);

  while(digitalRead(B1) == LOW && digitalRead(B2) == LOW && digitalRead(B3) == LOW);
  
  delay(50);
  if(digitalRead(B1) == HIGH) return 1;
  if(digitalRead(B2) == HIGH) return 2;
  if(digitalRead(B3) == HIGH) return 3;
  return 0;
}

void game_over(){
  for(int i =0; i<3; i++){
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  delay(200);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  delay(200);
  }
  delay(2000);
  counter = 0;
}


void game(int limit){
  for(int i=0;i<limit;i++){
    //wait until any button is pressed
	int button = get_button(); 
    
    //sometimes the button is stubborn - we need to make sure it was pressed
    if(button == 1) digitalWrite(LED1, HIGH);
    if(button == 2) digitalWrite(LED2, HIGH);
    if(button == 3) digitalWrite(LED3, HIGH);
    delay(200); 
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);

    if(button != seq[i]){
      game_over();
      return;
    }
    delay(1000);
  }
}

void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(B1, INPUT);
  pinMode(B2, INPUT);
  pinMode(B3, INPUT);
  counter = 0;
}

void loop()
{
  if(counter < 10){
    seq[counter] = random(1, 4);
    counter++; 
  }
  
  for(int i = 0; i < counter; i++){
    if(seq[i] == 1) digitalWrite(LED1, HIGH);
    if(seq[i] == 2) digitalWrite(LED2, HIGH);
    if(seq[i] == 3) digitalWrite(LED3, HIGH);
    delay(500);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    delay(500);
  }
  
  game(counter);
  
}