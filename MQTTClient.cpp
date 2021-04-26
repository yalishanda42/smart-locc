#include "MQTTClient.hpp"

MQTTClient::MQTTClient(const String mqttServer, const unsigned int mqttPort, const ClientData& clientData)
{ 
        this->mqttServer = mqttServer;
        this->mqttPort = mqttPort;
        this->clientData = clientData;
}

MQTTClient::MQTTClient(const MQTTClient& other)
{
  this->copyInternals(other);
}

MQTTClient& MQTTClient::operator=(const MQTTClient& other) {

    if (this != &other)
    {
        this->copyInternals(other );
    }

    return *this;
}

void MQTTClient::connect()
{
    pubSubClient.setClient(this->espClient);
    pubSubClient.setServer(mqttServer.c_str(), mqttPort);
}

void MQTTClient::connect(void (*callback)
    (char* topic, byte* payload, unsigned int length))
{
    this->connect();
    pubSubClient.setCallback(callback);
}

int MQTTClient::reconnect()
{
    Serial.println("Reconnect requested");
    if (pubSubClient.connected()) {
        Serial.println("MQTT client is still connected");
        return 0;
    }

    Serial.print("Reconnecting to MQTT server...");
    if (pubSubClient.connect(clientData.clientId.c_str(), 
        clientData.userToken.c_str(), clientData.pass.c_str())) {
        Serial.println("connected");
        Serial.println("resubscribed");
        return 0;
    }
    else {
        Serial.println("failed");
        return pubSubClient.state();
    }
}

void MQTTClient::publish(const String topic, const String payload)
{
    pubSubClient.publish(topic.c_str(), payload.c_str());
}

void MQTTClient::copyInternals(const MQTTClient &other)
{
        this->mqttServer = other.mqttServer;
        this->mqttPort = other.mqttPort;
        this->clientData = other.clientData;
}
