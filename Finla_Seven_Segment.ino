const int segment[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x00};
int numbers[] = {10, 10, 2, 3};

int count = 0;
int delta = 100;

void setup() {
  // put your setup code here, to run once:
  DDRB = B111111;
  DDRD = B11111110;
  Serial.begin(9600);
}

void loop() {
  updateParameter(count);
  
    for(int i = 0; i < 4; i ++){
      disp(numbers[i]);
      digitalWrite(10+i, LOW);
      
      if(i == 2 && count > delta){
        digitalWrite(9, HIGH);
      }
      delay(11);
    }
  count ++;
}

void disp(int num){
  PORTB = segment[num] >> 6;
  PORTD = segment[num] << 2;
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
}

void updateParameter(int c){
  
  if(c < delta) {
  	int gas = map(analogRead(0), 0, 1023, 0, 99);
    int bat = map(analogRead(1), 0, 1023, 0, 16);
    Serial.print(gas);
    Serial.print("\t");
    Serial.print(bat);
    Serial.println("\t1");
    numbers[0] = gas / 10;
    numbers[1] = gas % 10;
    numbers[2] = bat / 10;
    numbers[3] = bat % 10;
  }
  else if(c < 2*delta){ 
    
    float oil = mapfloat(analogRead(2), 0, 914, 25.0, 65.0);
    Serial.print(oil);
    Serial.println("\t2");
    numbers[0] = int(oil) / 100;
    numbers[1] = int(oil) / 10;
    numbers[2] = int(oil) % 10;
    numbers[3] = int(oil*10) % 10;
  }
  else if(c < 3*delta) {
    //
    float amb = mapfloat(analogRead(3), 20, 358, -40.0, 125.0);
    Serial.print(amb);
    Serial.println("\t3");
    numbers[0] = int(amb) / 100;
    numbers[1] = int(amb) / 10;
    numbers[2] = int(amb) % 10;
    numbers[3] = int(amb*10) % 10;
  }
  else if(c < 4*delta) {
    //
    float eng = mapfloat(analogRead(4), 20, 358, -40.0, 125.0);
    Serial.print(eng);
    Serial.println("\t4");
    numbers[0] = int(eng) / 100;
    numbers[1] = int(eng) / 10;
    numbers[2] = int(eng) % 10;
    numbers[3] = int(eng*10) % 10;
  }
  else{
    count = 0;
  }
}

float mapfloat(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}