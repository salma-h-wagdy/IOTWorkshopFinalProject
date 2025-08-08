#include <PubSubClient.h>

#include <ESP8266WiFi.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

#define ssid "ssid" 
#define pass "pass"

#define TH1 1500
#define TH2 3000
#define TH3 5000

#define IR_PIN D5

WiFiClient wclient;
PubSubClient client(wclient);

const char broker[]="broker.emqx.io";
const int port=1883;

long long lastPubTime=0;
long long lastPubTime2=0;
long long lastPubTime3=0;

float one = 6.0;
int two= 5;
const char obj[]  = "OBJECT DETECTED" ;
const char noObj[]  = "NO OBJ DETECTED" ;

char str[16];

char three[20] ;

int ir_value=0;

void setup() {

  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid,pass);
  while(WiFi.status()!=WL_CONNECTED){
    Serial.println(WiFi.status());
    delay(1000);
  }

  Serial.println("Wifi connected ! :D");
  Serial.println(WiFi.localIP());

  client.setServer(broker,port);

  
  //of course it wasn't client while i was using it, feel free to change it again :p
  while(!client.connect("client")){
    Serial.println("not yet");
    delay(1000);
  }

  Serial.println("Broker Connected :D");
  lastPubTime=millis();
  lastPubTime2=millis();
  lastPubTime3=millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  client.loop();

  
  if((millis()-lastPubTime)>= TH1){
      // gcvt(one,16,str);
     if(client.publish("/sectorb5/salma/Float",itoa(two,str,16))){
      
      Serial.println("publish 1 done?");
    
    }
    lastPubTime=millis();
  }

  if((millis()-lastPubTime2)>= TH2){
    if(client.publish("/sectorb5/salma/Int",itoa(two,str,16))){
      
      Serial.println("publish 2 done?");
    
    }
    lastPubTime2=millis();
  }    

  if((millis()-lastPubTime3)>= TH3){
   ir_value=digitalRead(IR_PIN); 

   if(ir_value==1){
    if(client.publish("/sectorb5/salma/IR",noObj)){
      
      Serial.println("publish 3 done?");
    
    }
   }

   else{
    if(client.publish("/sectorb5/salma/IR",obj)){
      
      Serial.println("publish 3 done?");
    
    }

   }
    
    lastPubTime3=millis();
  }

  // millis();


}
