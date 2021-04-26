//#include <WiFi.h>
//#include <WiFiManager.h>
//#include <PubSubClient.h>
//
//#define TOKEN "...." // Put your Ubidots' TOKEN
//#define VARIABLE_LABEL "..." // Assing the variable label
//#define VARIABLE_LABEL_2 "...." // Assing the variable label
//#define DEVICE_LABEL "...." // Assing the device label
//#define MQTT_CLIENT_NAME "...." // MQTT client Name
//
//#define TOPIC "/v1.6/devices/esp32-dht"
//#define VARIABLE_LABEL_TEMPERATURE "temperature"
//#define VARIABLE_LABEL_HUMIDITY "humidity" 
//
//// Update these with values suitable for your network.
//
//const char* mqttServer = "industrial.api.ubidots.com";
//const unsigned int mqttPort = 1883; // todo: use secured endpoints
//const char* clientId = "Pokemon";
//const char* user = "BBFF-PUFJ9U6latCE6QE7IUWFIAjBrmCOqg";
//const char* pass = ""; // not needed for auth, can be left blank
//
//void callback(char* topic, byte* payload, unsigned int length) {
//  Serial.print("Message received on topic [" + String(topic) + "]");
//  for (int i = 0; i < length; i++) {
//    Serial.print((char)payload[i]);
//  }
//  Serial.println();
//}
//
//WiFiClient espClient;
//PubSubClient client(mqttServer, mqttPort, callback, espClient);
//
//void setupWiFi() {
//
//  delay(10);
//  Serial.println();
//  Serial.print("Connecting to ");  
//  //WiFi.mode(WIFI_STA);
//  WiFiManager wm;  
//  bool res = wm.autoConnect();
//  
//}
//
//int reconnect() {
//  Serial.println("Reconnect requested");
//  if(client.connected()) {
//    Serial.println("MQTT client is still connected");
//    return 0;
//  }
//  
//  Serial.print("Reconnecting to MQTT server...");  
//  if (client.connect(clientId, user, pass)) {
//    Serial.println("connected");
//    
//    //client.subscribe("topics/2");
//    Serial.println("resubscribed");
//    return 0;
//    
//  } else {
//    Serial.println("failed");
//    return client.state();
//  }
//}
//
//bool sendValues(float temperature, float humidity)
//{
//  char json[250];
//  
//  //Atribui para a cadeia de caracteres "json" os valores referentes a temperatura e os envia para a variável do ubidots correspondente
//  sprintf(json,  "{\"%s\":{\"value\":%02.02f, \"context\":{\"temperature\":%02.02f, \"humidity\":%02.02f}}}", VARIABLE_LABEL_TEMPERATURE, temperature, temperature, humidity);  
// 
//  if(!client.publish(TOPIC, json))
//    return false;
// 
//  //Atribui para a cadeia de caracteres "json" os valores referentes a umidade e os envia para a variável do ubidots correspondente
//  sprintf(json,  "{\"%s\":{\"value\":%02.02f, \"context\":{\"temperature\":%02.02f, \"humidity\":%02.02f}}}", VARIABLE_LABEL_HUMIDITY, humidity, temperature, humidity);  
//       
//  if(!client.publish(TOPIC, json))
//    return false;
// 
//  //Se tudo der certo retorna true
//  return true;
//}
//
//void setup() {
//  Serial.begin(115200);
//  setupWiFi();
//  client.setServer(mqttServer, mqttPort);
//  client.setCallback(callback);
//}
//void loop() {
//  
//  float temperature = random(200, 301) / 10.0;
//
//  if (!client.connected()) {
//      reconnect();
//  } else{
//  client.loop();
//      
//    // TODO add sequence number
//    String temp = String(temperature,1);
//    sendValues(temperature, temperature);
//  }
//  delay(2000);
//}
