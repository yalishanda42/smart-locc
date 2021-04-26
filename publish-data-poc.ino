#include "StatsManager.hpp"

#define TOPIC "/v1.6/devices/esp32-dht"
#define VARIABLE_LABEL_TEMPERATURE "temperature"
#define VARIABLE_LABEL_HUMIDITY "humidity" 

String MQTTServer = "industrial.api.ubidots.com";
unsigned int MQTTPort = 1883;
String ClientId = "Pokemon";
String UserToken = "";
String Pass = "";
ClientData ClientData{ ClientId, UserToken, Pass };

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  MQTTClient client(MQTTServer, MQTTPort, ClientData);
  StatsManager stats(client);
  
  float temperature = random(200, 301) / 10.0;
  char json[250];
  sprintf(json,  "{\"%s\":{\"value\":%02.02f, \"context\":{\"temperature\":%02.02f, \"humidity\":%02.02f}}}",
  VARIABLE_LABEL_TEMPERATURE, temperature, temperature, temperature);  
  
  stats.postData(TOPIC, json);

  delay(2000);
}
