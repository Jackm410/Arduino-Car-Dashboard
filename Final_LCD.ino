#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
float totalDistance = 50000; // in meter
float tripDistance = 0;   // in meter

const float tireDiameter = 0.6604; // in Meter

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(7, INPUT);
  pinMode(10, INPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop()
{
  int start = millis();
  float freq = getFreq(7);
  float speed = getSpeed(freq);
  disp(totalDistance/1000, tripDistance/1000, int(freq*60), speed);
  updateDistance(start, speed);
  float dist = getDist(9, 10);
  //Serial.println(dist);
  breakCheck(dist, speed);
}

void breakCheck(float dist, float speed){
  if(dist < (speed*1)/3.6){
    digitalWrite(8, HIGH);
  }
}

void updateDistance(int start, float speed){
  float dx = speed * (millis() - start) * 0.001;
  //Serial.println(millis()-start);
  tripDistance += dx;
  totalDistance += dx;
}

float getFreq(int pin){
  float duration = pulseIn(pin, HIGH) / 1000.0;
  float freq = 1/(duration*0.002);
  //Serial.print(duration);Serial.print("\t");Serial.println(freq);
  return freq;
}

float getSpeed(float freq){
  float speed = 3.1415926 * tireDiameter * freq;
  return speed;  // in m/s
}

void disp(float m, float d, int rpm, float v){
  String str1 = "D=" + String(d, 1) + "M=" + String(m, 1);
  String str2 = "S=" + String(v, 1) + "RPM=" + String(rpm);
  lcd.setCursor(0, 0);
  lcd.print(str1);
  lcd.setCursor(0, 1);
  lcd.print(str2);
}

float getDist(int trigPin, int echoPin){
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2);  
  digitalWrite(trigPin, HIGH);  
  delayMicroseconds(10);  
  digitalWrite(trigPin, LOW); 
  float duration = pulseIn(echoPin, HIGH); 
  float dist = (duration*0.0343)/2;
  return dist;
}
