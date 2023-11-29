#include <SoftwareSerial.h>

SoftwareSerial espSerial(2, 3);

int trig = 5;
int echo = 4, motor = 10;
int adcHumi = A0;
int value, distance, DataHumi, valueHumi;
unsigned long last ;

void mucnuoc();
void humidity();

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(motor, OUTPUT);

  Serial.begin(9600);
  espSerial.begin(115200);  

  last = millis();
}

void loop() {
  
  // if( millis() - last >= 1000)
  // {
  mucnuoc();
  humidity();
  // last = millis();
  // }

}

void mucnuoc()
{
  digitalWrite(trig, LOW);
  delay(2);
  digitalWrite(trig, HIGH);
  delay(5);
  digitalWrite(trig, LOW);

  value = pulseIn(echo, HIGH);

  distance = value/2/29.412 ;

  Serial.print(distance);
  Serial.println("cm");
  espSerial.print(distance);
  espSerial.print(",");
}

void humidity()
{
  
  int percent = map(analogRead(adcHumi), 350, 1023, 0, 100);
  percent = 100 - percent;
  if (percent <=20)
  {
    digitalWrite(motor, HIGH);
  }
  else if(percent >= 60)
  {
    digitalWrite(motor, LOW);
  }
  Serial.println(percent);
  espSerial.print(percent);

}