// #include <ArduinoWiFiServer.h>
// #include <BearSSLHelpers.h>
// #include <CertStoreBearSSL.h>
// #include <ESP8266WiFi.h>
// #include <ESP8266WiFiAP.h>
// #include <ESP8266WiFiGeneric.h>
// #include <ESP8266WiFiGratuitous.h>
// #include <ESP8266WiFiMulti.h>
// #include <ESP8266WiFiSTA.h>
// #include <ESP8266WiFiScan.h>
// #include <ESP8266WiFiType.h>
// #include <WiFiClient.h>
// #include <WiFiClientSecure.h>
// #include <WiFiClientSecureBearSSL.h>
// #include <WiFiServer.h>
// #include <WiFiServerSecure.h>
// #include <WiFiServerSecureBearSSL.h>
// #include <WiFiUdp.h>

#include <ESP8266WiFi.h>
// #define IR_PIN D5

#define ssid "ssid" 
#define pass "pass"

// int ir_value=0;

void setup()
{	
 Serial.begin(9600);
 WiFi.begin(ssid,pass);
 while(WiFi.status()!=WL_CONNECTED){
  Serial.println(WiFi.status());
 }
 Serial.println("Wifi connected ! :D");
 Serial.println(WiFi.localIP());
 
  /*Serial.begin(9600);
  pinMode(IR_PIN, INPUT);*/ 
  //pinMode(6, OUTPUT);
  //pinMode(4,INPUT);
}

void loop()
{
  
  
  
  /*//if(Serial.available()){
   //int x = Serial.parseInt(); 
   ir_value=digitalRead(IR_PIN);

   if(ir_value==1){
    Serial.println("NO OBJECT DETECTED");
    delay(3000);
   }

   else{
    Serial.println("OBJECT DETECTED");
    delay(3000);

   }
  //  Serial.println(ir_value);
  //  delay(1000);
   
   
   /*Serial.println(x);
    if(x==0){
      digitalWrite(2,LOW);
      digitalWrite(6,LOW);
    }
    else if(x==1){
      digitalWrite(2,HIGH);
      digitalWrite(6,LOW);
    }
    else if(x==2){
      digitalWrite(2,LOW);
      digitalWrite(6,HIGH);
    }
    else if(x==3){
      digitalWrite(2,HIGH);
      digitalWrite(6,HIGH);
    }
    else{
      Serial.println("INVALID INPUT");
    }*/
 // }*/
} 
