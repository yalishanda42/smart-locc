#ifndef __MQTT_CLIENT__HPP__
#define __MQTT_CLIENT__HPP__

#include <PubSubClient.h>
#include <WiFi.h>
#include "ClientData.hpp"
#include <cstring>

class MQTTClient {
public:
  MQTTClient();
	MQTTClient(const String mqttServer,
		const unsigned int mqttPort, 
		const ClientData& clientData);

	MQTTClient(const MQTTClient&);
	MQTTClient& operator=(const MQTTClient&);

	void connect();
	void connect(void (*callback)
		(char* topic, byte* payload, unsigned int length));

	int reconnect();

	void publish(const String topic, const String payload);
private:
	String mqttServer;
	unsigned int mqttPort;
	ClientData clientData;

  WiFiClient espClient;
  PubSubClient pubSubClient;
  
  void setupWiFi();
  void copyInternals(const MQTTClient &other);
};

#endif
