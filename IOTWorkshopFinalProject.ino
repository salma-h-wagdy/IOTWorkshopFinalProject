// libraries
#include <PubSubClient.h>

#include <ESP8266WiFi.h>

#include <string.h>

// constant interval to publish message
#define TH 1000

// insert correct credentials here
#define ssid "ssid"
#define pass "password"

// esp pins used
#define IR_PIN D5
#define LED_PIN D1

// wifi client
WiFiClient wclient;
PubSubClient client(wclient);

// broker we used, can be changed
const char broker[] = "broker.emqx.io";
const int port = 1883;

// vars
const char obj[] = "object";
const char noObj[] = "noobject";

int ir_value = 0;

// char* on="on";

long long lastPubTime = 0;

char str[16];

int i = 0;

// callback function at recieving a message from a topic that's been subscribed to, in this code that's the switch :D
void callback(char topic[], byte *payload, unsigned int length)
{

  Serial.println(topic);

  Serial.print("Message:");

  for (i = 0; i < length; i++)
  {
    str[i] = (char)payload[i];
  }
  str[i] = '\0';
  char *x = str;
  Serial.println(x);

  if (strcmp(str, "on") == 0)
  {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("on");
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
    Serial.println("off");
  }
}

void setup()
{
  Serial.begin(9600);

  pinMode(IR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  // connection to wifi
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println(WiFi.status());
    delay(1000);
  }

  Serial.println("Wifi connected ! :D");
  Serial.println(WiFi.localIP());

  // set broker
  client.setServer(broker, port);

  // set callback function
  client.setCallback(callback);

  // insert unique client-id here to connect to the broker
  while (!client.connect("unique-client-id"))
  {
    Serial.println("not yet connected to broker");
    delay(1000);
  }

  Serial.println("Broker Connected :D");

  // subscribe to subject, in this case a switch
  while (!client.subscribe("/sectorb5/salma/switch"))
  {
    Serial.println("subscribing");
    delay(500);
  }

  Serial.println("subscribed to ../switch");

  // to publish at set intervals
  lastPubTime = millis();
}

void loop()
{
  client.loop();

  // publish ir sensor state and print confirmation

  if ((millis() - lastPubTime) >= TH)
  {
    ir_value = digitalRead(IR_PIN);

    if (ir_value == 1)
    {
      if (client.publish("/sectorb5/salma/IR", noObj))
      {

        Serial.println("publish 3 done?");
      }
    }

    else
    {
      if (client.publish("/sectorb5/salma/IR", obj))
      {

        Serial.println("publish 3 done?");
      }
    }

    lastPubTime = millis();
  }
}
