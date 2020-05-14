#include <FirebaseArduino.h>
#include  <ESP8266WiFi.h>
#include<SoftwareSerial.h>
SoftwareSerial SUART(4, 5); //SRX=Dpin-D2; STX-DPin-D1
//-------------------------
#define FIREBASE_HOST "energy-meter-ebe6d.firebaseio.com"                          // the project name address from firebase id
#define FIREBASE_AUTH "j6KPjN4Kmgl155QZUjKGUXBKwkc9cVkRXpNUT1oD"            // the secret key generated from firebase

#define WIFI_SSID "ThingSenz"                                             // input your home or public wifi name 
#define WIFI_PASSWORD "qwertypoiu123"  
//--------------------------------------------

int val1;
String s0,s1,s2,s3;
int W;
String w;
int val =0 ; // variable for reading the pin status

void setup()
{
  pinMode(16, OUTPUT);
  Serial.begin(115200); //enable Serial Monitor
  SUART.begin(115200); //enable SUART Port
WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.setInt("S1",0);


  
  
}

}
void firebasereconnect()
{
  Serial.println("Trying to reconnect");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  }
void loop()
{
   byte n = SUART.available(); //n != 0 means a character has arrived
  while (n != 0)
  {
    s0 = SUART.readStringUntil(',');
    SUART.read();
   //Serial.print(s0);
   
     s1 = SUART.readStringUntil(',');
   //Serial.println(s1);
    SUART.read();
     s2 = SUART.readStringUntil(',');
      s3 = SUART.readStringUntil('\\');//read character
   //al.println(s2);     //show character on Serial Monitor       //show character on Serial Monitor
//    fw=s.substring(0,80);
     
   // Firebase.setString("threshold",threshold);
  //  Firebase.setString ("Usage",fw);
     Firebase.setString ("/Power",s0);
      Firebase.setString ("/Energy",s1);
       Firebase.setString ("/Bill",s2);
  
  // read input value

  val=Firebase.getString("S1").toInt();
 
  
    Serial.print(val);
  if (val==1)
  {
    digitalWrite(16,0);
    Serial.println("light 1 ON");
  }
  else
  {
digitalWrite(16,1);
  Serial.println("light 1 OFF");
  }
  }

  
  
}
