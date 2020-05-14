/*
//This code is to uploaded to the arduino uno
Created for testing purpose- ThingSenZ

*/
#include<SoftwareSerial.h>
#include <stdlib.h>
SoftwareSerial SUART(2, 3); //SRX=Dpin-2; STX-DPin-3

const int sensorIn = A0;
int mVperAmp = 66; // use 100 for 20A Module and 66 for 30A Module
float Time = 0.0;
float TotalWh = 0.0;
float AmpSeconds = 0.0;
float AmpHours = 0.0;
float WattHours = 0.0;
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;
float V = 220;
float Amount ;
float Totalbill ;
String stringdata="";
String swatt="";
String senergy="";
String samount="";
String stime="";
String stringdata0="";
float threshold=1;



void setup()
{
  Serial.begin(115200); //enable Serial Monitor
  SUART.begin(115200); //enable SUART Port
pinMode(A0,INPUT);
}

void loop()
{

  Voltage = getVPP();
 VRMS = ((Voltage/2.0) *0.7072135)-0.01;  //root 2 is 0.707
 AmpsRMS = ((VRMS * 1000)/mVperAmp)-0.03;
float C=AmpsRMS-0.02;
  float Watt = (((V * (AmpsRMS))-0.45)*1.15)+0.066;
  float msec = millis();
  Time = (float) msec / 1000.0;
  AmpSeconds = (AmpsRMS) *2;
  AmpHours = AmpSeconds / 3600;
  WattHours = V * AmpHours;
  TotalWh = TotalWh + WattHours;
  Amount = (WattHours/1000)*3.5;
  Totalbill += Amount;
//Serial.print("\t TotalWh (Wh)=");
 //   Serial.print(TotalWh);
    swatt = Watt;
    senergy=TotalWh;
    samount=Totalbill;
   stime= Time;
     // Serial.println(Watt);
     // 
  SUART.print( swatt +",");
      SUART.print(senergy +",");
        SUART.print(samount+",");
        SUART.print(stime+"");
   // SUART.println();
   Serial.println(swatt); 
Serial.println(senergy);
Serial.println(samount); 
Serial.println(stime);
  //delay(1000);
 
  

}
float getVPP()
{
  float result;
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1023;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 2000) //sample for 3 Sec
   {
       readValue = analogRead(sensorIn);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1023.0;   
   return result;
}
