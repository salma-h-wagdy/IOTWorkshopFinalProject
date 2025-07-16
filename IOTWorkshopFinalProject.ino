#include <PubSubClient.h>

#include <ESP8266WiFi.h>

#include <string.h>

#define TH 1000

#define ssid "Accio wifi" 
#define pass "12345678"

#define IR_PIN D5
#define LED_PIN D1

WiFiClient wclient;
PubSubClient client(wclient);

const char broker[]="broker.emqx.io";
const int port=1883;


const char obj[]  = "object" ;
const char noObj[]  = "noobject" ;

int ir_value=0;

// char* on="on";

long long lastPubTime=0;

char str[16];

int i =0;


void callback(char topic[],byte* payload,unsigned int length){
  
  Serial.println(topic);
  

  Serial.print("Message:");
  
  for( i=0;i<length;i++){
   str[i] = (char)payload[i];

  }
  str[i]='\0';
  char * x = str;
   Serial.println(x);

  if(strcmp(str,"on")==0){
    digitalWrite(LED_PIN,HIGH);
    Serial.println("on");
  }
  else{
    digitalWrite(LED_PIN,LOW);
    Serial.println("off");
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(IR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  WiFi.begin(ssid,pass);


  while(WiFi.status()!=WL_CONNECTED){
    Serial.println(WiFi.status());
    delay(1000);
  }

  Serial.println("Wifi connected ! :D");
  Serial.println(WiFi.localIP());

  client.setServer(broker,port);
  client.setCallback(callback);

  

  while(!client.connect("salmahwagdy")){
    Serial.println("not yet");
    delay(1000);
  }

  Serial.println("Broker Connected :D");

  lastPubTime=millis();

   while(!client.subscribe("/sectorb5/salma/switch")){
    Serial.println("subscribing");
    delay(500);
  }

  Serial.println("subscribed to ../switch");

  
}





void loop() {
  client.loop();


  if((millis()-lastPubTime)>= TH){
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
    
    lastPubTime=millis();
  }
}
