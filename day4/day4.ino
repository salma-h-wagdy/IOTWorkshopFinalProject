#include <PubSubClient.h>

#include <ESP8266WiFi.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

#define ssid "ssid" 
#define pass "pass"

#define TH1 2000

WiFiClient wclient;
PubSubClient client(wclient);

const char broker[]="broker.emqx.io";
const int port=1883;

long long lastPubTime=0;

const char str[]  = "Hello :D" ;

void callback(char topic[],byte* payload,unsigned int length){
  
  Serial.println(topic);
  

  Serial.print("Message:");

  for(int i=0;i<length;i++){
    Serial.print((char)payload[i]);

  }
  Serial.println(" ");
}

void setup() {

  Serial.begin(9600);

  WiFi.begin(ssid,pass);
  while(WiFi.status()!=WL_CONNECTED){
    Serial.println(WiFi.status());
    delay(1000);
  }

  Serial.println("Wifi connected ! :D");
  Serial.println(WiFi.localIP());


  client.setServer(broker,port);
  client.setCallback(callback);

  //again, changed it to client :D
  while(!client.connect("client")){
    Serial.println("not yet");
    delay(1000);
  }

  Serial.println("Broker Connected :D");
  
  while(!client.subscribe("/sectorb5/salma/#")){
    Serial.println("subscribing");
    delay(500);
  }

  Serial.println("subscribed to ../received");

   lastPubTime=millis();
}

void loop() {
  client.loop();

  if((millis()-lastPubTime)>= TH1){
      // gcvt(one,16,str);
     if(client.publish("/sectorb5/salma/publish",str)){
      
      Serial.println("publish done?");
    
    }
    lastPubTime=millis();
  }
  

}
