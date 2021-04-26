#ifndef __STATS_MANAGER__HPP__
#define __STATS_MANAGER__HPP__

#include <WiFi.h>
#include <WiFiManager.h>
#include "MQTTClient.hpp"

class StatsManager {
public: 
	StatsManager(MQTTClient &client);
 
	void postData(const String topic, const String payload);
private:
	MQTTClient client;
  bool wifiSetup = false;

	void setupWiFi();
};

#endif
