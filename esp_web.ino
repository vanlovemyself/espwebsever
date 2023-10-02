
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include "web.h"


IPAddress ip(192, 168, 0, 11);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(8, 8, 8, 8);

ESP8266WebServer sv(80);
SoftwareSerial adnSerial(D2,D3);

String chuoiSendWebJson = "";
float temp ;
float humi ;
int valueData, distance, motor, led;
int led1 = D5, led2 = D6, led3 = D7, led4 = D8;
unsigned long last ;


void onled1();
void offled1();
void volume();
void temperature();
void humidity();
void waterLevel();
void status();
void send_Update();
void DataJson(String sensor1, String sensor2, String sensor3, String sensor4, String sensor5);


void setup() {
 
  //WiFi.mode(WIFI_AP_STA);
  pinMode(D0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  adnSerial.begin(115200);
  
  const char *ssid = "Hung Le 1";
  const char *password = "t@msot@m";

  WiFi.begin(ssid,password);
  Serial.begin(115200);
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }

  WiFi.config(ip, gateway, subnet, dns);

  Serial.println("Connected to WiFi");
  WiFi.softAP("Quan Van qua dinh", "12345678");
  Serial.print("IP address is :");
  Serial.println(WiFi.localIP());
  
  sv.on("/",[]{
  sv.send(200,"text/html", webpage );
  });
  sv.on("/bat1", onled1 );
  sv.on("/tat1", offled1);
  sv.on("/Update", [] {
    send_Update();
  });
  sv.begin();


  last = millis();
}

void loop() {
 sv.handleClient();

  if (millis() - last >= 1000)
    {
    volume();
    temperature();
    //humidity();
    //status();
   last = millis();
    }

    waterLevel();


}


void send_Update()
  {
    DataJson(String(distance), String(temp), String(humi), String(led), String(motor));
  sv.send(200, "text/html", String(chuoiSendWebJson) );
  }
void DataJson(String sensor1, String sensor2, String sensor3, String sensor4, String sensor5)
  {
    chuoiSendWebJson = "{\"MN\":\"" + String(sensor1) + "\"," +
                       "\"ND\":\"" + String(sensor2) + "\"," +
                       "\"DA\":\"" + String(sensor3) + "\"," + 
                       "\"TTL\":\"" + String(sensor4) + "\"," +
                       "\"TTDC\":\"" + String(sensor5) + "\"}"; 
  }

void volume()
{
  if (adnSerial.available())
  {
    String inputData = adnSerial.readStringUntil('/n');

    
    inputData.trim();

    valueData = inputData.substring(0, inputData.indexOf(',')).toInt();
    humi = inputData.substring(inputData.indexOf(',') + 1).toInt();
    if(humi <=20)
    {
      motor = 1;
    }
    else if(humi >= 60)
    {
      motor = 0;
    }
    
    
    distance = valueData * 10 * 5;
    
    Serial.print("muc nuoc:");
    Serial.println(distance);
     Serial.print("doam:");
      Serial.println(humi);
  }
}

void temperature()
{
  temp = analogRead(A0);
}

void waterLevel()
{
  if (valueData > 40)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);

  }
  else  if (valueData > 30)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);

  }
  else  if (valueData > 20)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);

  }
   else  if (valueData > 10)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);

  }
   else  if (valueData > 5)
  {
    digitalWrite(led1, HIGH);
    delay(10);
    digitalWrite(led1, LOW);
    delay(10);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);

  }
}
void onled1()
  {
  digitalWrite(D0, HIGH);
  led = 1;
  Serial.println("bật led 1");
  sv.send(200,"text/html", webpage );
  }

void offled1()
  {
  digitalWrite(D0, LOW);
  led = 0;
  Serial.println("tắt led 1");
  sv.send(200,"text/html", webpage );
  }
