#include <FirebaseArduino.h>
#include  <ESP8266WiFi.h>
#include<SoftwareSerial.h>
//const int ProxSensor=5;
int relay = 16;
 int relay1 = 0;
 int ldrPin = A0;
#define FIREBASE_HOST "energy-meter-ebe6d.firebaseio.com"                          // the project name address from firebase id
#define FIREBASE_AUTH "j6KPjN4Kmgl155QZUjKGUXBKwkc9cVkRXpNUT1oD"            // the secret key generated from firebase
#define WIFI_SSID "ThingSenz"                                             // input your home or public wifi name 
#define WIFI_PASSWORD "qwertypoiu123"
int x=0;
void setup() 
{                
   pinMode(relay1, OUTPUT);
  pinMode(ldrPin, INPUT);
  Serial.begin(115200);
WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
}
}
void firebasereconnect()
{
  Serial.println("Trying to reconnect");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  }
void loop() 
{
  //String modes;
x=Firebase.getString ("Mode").toInt();
Serial.println(x);
if(x!=0)
{
  int led=14;
  analogWrite(led,150);
  
}
else 
{
 digitalWrite(16,1);
 digitalWrite(14,1);  
}

int ldrStatus = analogRead(ldrPin);
Serial.print(analogRead(ldrPin));
  if (ldrStatus <= 500) {
    digitalWrite(relay1, HIGH);
    Serial.println("bright, Street Light is OFF");
  }

  else {
    digitalWrite(relay1, LOW);
    Serial.println("light ON");
  }
}


  
