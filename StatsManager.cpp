#include "StatsManager.hpp"

StatsManager::StatsManager(MQTTClient &client) : client(client)
{
  if(!wifiSetup) 
  {
    this->setupWiFi();
    this->wifiSetup = true;
  }  
}

void StatsManager::postData(const String topic, const String payload)
{
	client.publish(topic, payload);
}

void StatsManager::setupWiFi()
{
	delay(10);
	Serial.println();
	Serial.print("Connecting to ");
	//WiFi.mode(WIFI_STA);
	WiFiManager wm;
	bool res = wm.autoConnect();

	client.connect();
}
