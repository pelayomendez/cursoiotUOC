/*
 * MKR RELAY Mqtt Control
 * 
 * Lectura y control de los realys del shield via mqtt
 *
 */

#include <ArduinoMqttClient.h>
#include <WiFi101.h>

// Wifi Connection:
WiFiClient wifiClient;
char ssid[] = ""; 
char pass[] = "";
int status = WL_IDLE_STATUS;

// Mqtt client:
MqttClient mqttClient(wifiClient);
const char broker[] = "192.168.1.145";
int        port     = 1884;
bool mqttclientconnected = false;

// Variable configuration HOMIE:
String HOMIE_VERSION = "3.0";
String DEVICE_NAME = "mkr10000";
String DEVICE_STATE = "ready";
String NODE_NAME = "mkrelay";

String topic_device   = "homie/" + DEVICE_NAME + "/";
String topic_node     = topic_device + NODE_NAME + "/";
String topic_node_sensor_relay1  = topic_node + "relay1";
String topic_node_sensor_relay2  = topic_node + "relay2";

String topic_node_sensor_relay1_set  = topic_node_sensor_relay1 + "/set";
String topic_node_sensor_relay2_set  = topic_node_sensor_relay2 + "/set";

// Relay Control
const int relay1 = 1;
const int relay2 = 2;
unsigned long previousMillis = 0;

void setup() {

  // Inicializamos los relays y los ponemos a 0
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  
  // Esperamos que el Serial este conectado:
  Serial.begin(9600);
  while (!Serial);
  
  // Conectamos el shield
  /*
  Serial.println("Inicializando MKR ENV shield");
  if (!ENV.begin()) {
    Serial.println("Error inicializando MKR ENV shield");
    while (1);
  }
  */

  // Conectamos a la red WIFI
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);

    delay(10000);
  }

  Serial.println("You're connected to the network");

  // Fijamos un Id para que el servidor MQTT nos reconozca:
  //mqttClient.setId("mkr10000");
  // Le damos las credenciales del servidor que hemos configurado anteriormente:
  // mqttClient.setUsernamePassword("cursoiot", "iot.2019");
  // Conectamos al broker
  while (!mqttclientconnected) {
    mqttclientconnected = mqttClient.connect(broker, port);
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    
    delay(10000);
  }

  publishGenericHomieTopics();

  // Callback de mensajes
  mqttClient.onMessage(onMqttMessage);

  Serial.print("Subscribing to topic: ");
  Serial.println(topic_node_sensor_relay1_set);
  Serial.println();

  // subscribe to a topic
  mqttClient.subscribe(topic_node_sensor_relay1_set);

  Serial.println("Ready to go!");
}

// TODO: Retention policy
void publishGenericHomieTopics() {
  publishTopic(topic_device + "$homie", HOMIE_VERSION);
  publishTopic(topic_device + "$name", DEVICE_NAME);
  publishTopic(topic_device + "$state", DEVICE_STATE);
  publishTopic(topic_device + "$nodes", NODE_NAME);

  publishTopic(topic_node + "$name", NODE_NAME);
  publishTopic(topic_node + "$properties", "relay1");
  publishTopic(topic_node + "$properties", "relay2");
}


void publishTopic(String topic, String value) 
{  
    Serial.print("Sending message Topic: ");
    Serial.print(topic);
    Serial.print(" Value: ");
    Serial.println(value);
    
    mqttClient.beginMessage(topic);
    mqttClient.print(value);
    mqttClient.endMessage();
}

void loop()
{
  // Vamos a publicar el valor de los sensores en el servidoir MQTT cada 5 segundos
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 5000)
  {  
    // Mandamos la señal de KEEP_ALIVE al broker para que no nos desconecte:
    mqttClient.poll();
    
    // Update Realys info
    
    bool relay1_state = false;
    if(digitalRead(relay1) == HIGH) relay1_state = true;
  
    bool relay2_state = false;
    if(digitalRead(relay2) == HIGH) relay2_state = true;
   
    // Publish info
    
    Serial.print("relay1_state = ");
    Serial.println(relay1_state);

    publishTopic(topic_node_sensor_relay1, String(relay1_state));

    Serial.print("relay2_state = ");
    Serial.println(relay2_state);

    publishTopic(topic_node_sensor_relay2, String(relay2_state));
    
    Serial.println();
    
    previousMillis/*
 * MKR RELAY Mqtt Control
 * 
 * Lectura y control de los realys del shield via mqtt
 *
 */

#include <ArduinoMqttClient.h>
#include <WiFi101.h>

// Wifi Connection:
WiFiClient wifiClient;
char ssid[] = "Can Pelma"; 
char pass[] = "Olaya2014";
int status = WL_IDLE_STATUS;

// Mqtt client:
MqttClient mqttClient(wifiClient);
const char broker[] = "192.168.1.145";
int        port     = 1884;
bool mqttclientconnected = false;

// Variable configuration HOMIE:
String HOMIE_VERSION = "3.0";
String DEVICE_NAME = "mkr10000";
String DEVICE_STATE = "ready";
String NODE_NAME = "mkrelay";

String topic_device   = "homie/" + DEVICE_NAME + "/";
String topic_node     = topic_device + NODE_NAME + "/";
String topic_node_sensor_relay1  = topic_node + "relay1";
String topic_node_sensor_relay2  = topic_node + "relay2";

String topic_node_sensor_relay1_set  = topic_node_sensor_relay1 + "/set";
String topic_node_sensor_relay2_set  = topic_node_sensor_relay2 + "/set";

// Relay Control
const int relay1 = 1;
const int relay2 = 2;
unsigned long previousMillis = 0;

void setup() {

  // Inicializamos los relays y los ponemos a 0
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  
  // Esperamos que el Serial este conectado:
  Serial.begin(9600);
  while (!Serial);
  
  // Conectamos el shield
  /*
  Serial.println("Inicializando MKR ENV shield");
  if (!ENV.begin()) {
    Serial.println("Error inicializando MKR ENV shield");
    while (1);
  }
  */

  // Conectamos a la red WIFI
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);

    delay(10000);
  }

  Serial.println("You're connected to the network");

  // Fijamos un Id para que el servidor MQTT nos reconozca:
  //mqttClient.setId("mkr10000");
  // Le damos las credenciales del servidor que hemos configurado anteriormente:
  // mqttClient.setUsernamePassword("cursoiot", "iot.2019");
  // Conectamos al broker
  while (!mqttclientconnected) {
    mqttclientconnected = mqttClient.connect(broker, port);
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    
    delay(10000);
  }

  publishGenericHomieTopics();

  // Callback de mensajes
  mqttClient.onMessage(onMqttMessage);

  Serial.print("Subscribing to topic: ");
  Serial.println(topic_node_sensor_relay1_set);
  Serial.println();

  // subscribe to a topic
  mqttClient.subscribe(topic_node_sensor_relay1_set);

  Serial.println("Ready to go!");
}

// TODO: Retention policy
void publishGenericHomieTopics() {
  publishTopic(topic_device + "$homie", HOMIE_VERSION);
  publishTopic(topic_device + "$name", DEVICE_NAME);
  publishTopic(topic_device + "$state", DEVICE_STATE);
  publishTopic(topic_device + "$nodes", NODE_NAME);

  publishTopic(topic_node + "$name", NODE_NAME);
  publishTopic(topic_node + "$properties", "relay1");
  publishTopic(topic_node + "$properties", "relay2");
}


void publishTopic(String topic, String value) 
{  
    Serial.print("Sending message Topic: ");
    Serial.print(topic);
    Serial.print(" Value: ");
    Serial.println(value);
    
    mqttClient.beginMessage(topic);
    mqttClient.print(value);
    mqttClient.endMessage();
}

void loop()
{
  // Vamos a publicar el valor de los sensores en el servidoir MQTT cada 5 segundos
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 5000)
  {  
    // Mandamos la señal de KEEP_ALIVE al broker para que no nos desconecte:
    mqttClient.poll();
    
    // Update Realys info
    
    bool relay1_state = false;
    if(digitalRead(relay1) == HIGH) relay1_state = true;
  /*
 * MKR RELAY Mqtt Control
 * 
 * Lectura y control de los realys del shield via mqtt
 *
 */

#include <ArduinoMqttClient.h>
#include <WiFi101.h>

// Wifi Connection:
WiFiClient wifiClient;
char ssid[] = "Can Pelma"; 
char pass[] = "Olaya2014";
int status = WL_IDLE_STATUS;

// Mqtt client:
MqttClient mqttClient(wifiClient);
const char broker[] = "192.168.1.145";
int        port     = 1884;
bool mqttclientconnected = false;

// Variable configuration HOMIE:
String HOMIE_VERSION = "3.0";
String DEVICE_NAME = "mkr10000";
String DEVICE_STATE = "ready";
String NODE_NAME = "mkrelay";

String topic_device   = "homie/" + DEVICE_NAME + "/";
String topic_node     = topic_device + NODE_NAME + "/";
String topic_node_sensor_relay1  = topic_node + "relay1";
String topic_node_sensor_relay2  = topic_node + "relay2";

String topic_node_sensor_relay1_set  = topic_node_sensor_relay1 + "/set";
String topic_node_sensor_relay2_set  = topic_node_sensor_relay2 + "/set";

// Relay Control
const int relay1 = 1;
const int relay2 = 2;
unsigned long previousMillis = 0;

void setup() {

  // Inicializamos los relays y los ponemos a 0
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  
  // Esperamos que el Serial este conectado:
  Serial.begin(9600);
  while (!Serial);
  
  // Conectamos el shield
  /*
  Serial.println("Inicializando MKR ENV shield");
  if (!ENV.begin()) {
    Serial.println("Error inicializando MKR ENV shield");
    while (1);
  }
  */

  // Conectamos a la red WIFI
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);

    delay(10000);
  }

  Serial.println("You're connected to the network");

  // Fijamos un Id para que el servidor MQTT nos reconozca:
  //mqttClient.setId("mkr10000");
  // Le damos las credenciales del servidor que hemos configurado anteriormente:
  // mqttClient.setUsernamePassword("cursoiot", "iot.2019");
  // Conectamos al broker
  while (!mqttclientconnected) {
    mqttclientconnected = mqttClient.connect(broker, port);
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    
    delay(10000);
  }

  publishGenericHomieTopics();

  // Callback de mensajes
  mqttClient.onMessage(onMqttMessage);

  Serial.print("Subscribing to topic: ");
  Serial.println(topic_node_sensor_relay1_set);
  Serial.println();

  // subscribe to a topic
  mqttClient.subscribe(topic_node_sensor_relay1_set);

  Serial.println("Ready to go!");
}

// TODO: Retention policy
void publishGenericHomieTopics() {
  publishTopic(topic_device + "$homie", HOMIE_VERSION);
  publishTopic(topic_device + "$name", DEVICE_NAME);
  publishTopic(topic_device + "$state", DEVICE_STATE);
  publishTopic(topic_device + "$nodes", NODE_NAME);

  publishTopic(topic_node + "$name", NODE_NAME);
  publishTopic(topic_node + "$properties", "relay1");
  publishTopic(topic_node + "$properties", "relay2");
}


void publishTopic(String topic, String value) 
{  
    Serial.print("Sending message Topic: ");
    Serial.print(topic);
    Serial.print(" Value: ");
    Serial.println(value);
    
    mqttClient.beginMessage(topic);
    mqttClient.print(value);
    mqttClient.endMessage();
}

void loop()
{
  // Vamos a publicar el valor de los sensores en el servidoir MQTT cada 5 segundos
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 5000)
  {  
    // Mandamos la señal de KEEP_ALIVE al broker para que no nos desconecte:
    mqttClient.poll();
    
    // Update Realys info
    
    bool relay1_state = false;
    if(digitalRead(relay1) == HIGH) relay1_state = true;
  
    bool relay2_state = false;
    if(digitalRead(relay2) == HIGH) relay2_state = true;
   
    // Publish info
    
    Serial.print("relay1_state = ");
    Serial.println(relay1_state);

    publishTopic(topic_node_sensor_relay1, String(relay1_state));

    Serial.print("relay2_state = ");
    Serial.println(relay2_state);

    publishTopic(topic_node_sensor_relay2, String(relay2_state));
    
    Serial.println();
    
    previousMillis = currentMillis;
  }
}

void onMqttMessage(int messageSize)
{
  String msg   = "";
  String topic = mqttClient.messageTopic();
  Serial.println("Received a message with topic '");
  Serial.println(mqttClient.messageTopic());

  // use the Stream interface to print the contents
  while (mqttClient.available()) {
    msg += (char)mqttClient.read();
  }
  Serial.println(msg);

  if(topic == topic_node_sensor_relay1_set)
  {
    if(msg == "1") digitalWrite(relay1, HIGH);
    if(msg == "0") digitalWrite(relay1, LOW);
  }  

  if(topic == topic_node_sensor_relay2_set)
  {
    if(msg == "1") digitalWrite(relay2, HIGH);
    if(msg == "0") digitalWrite(relay2, LOW);
  }  

  Serial.println();
}

    bool relay2_state = false;
    if(digitalRead(relay2) == HIGH) relay2_state = true;
   
    // Publish info
    
    Serial.print("relay1_state = ");
    Serial.println(relay1_state);

    publishTopic(topic_node_sensor_relay1, String(relay1_state));

    Serial.print("relay2_state = ");
    Serial.println(relay2_state);

    publishTopic(topic_node_sensor_relay2, String(relay2_state));
    
    Serial.println();
    
    previousMillis = currentMillis;
  }
}

void onMqttMessage(int messageSize)
{
  String msg   = "";
  String topic = mqttClient.messageTopic();
  Serial.println("Received a message with topic '");
  Serial.println(mqttClient.messageTopic());

  // use the Stream interface to print the contents
  while (mqttClient.available()) {
    msg += (char)mqttClient.read();
  }
  Serial.println(msg);

  if(topic == topic_node_sensor_relay1_set)
  {
    if(msg == "1") digitalWrite(relay1, HIGH);
    if(msg == "0") digitalWrite(relay1, LOW);
  }  

  if(topic == topic_node_sensor_relay2_set)
  {
    if(msg == "1") digitalWrite(relay2, HIGH);
    if(msg == "0") digitalWrite(relay2, LOW);
  }  

  Serial.println();
}
 = currentMillis;
  }
}

void onMqttMessage(int messageSize)
{
  String msg   = "";
  String topic = mqttClient.messageTopic();
  Serial.println("Received a message with topic '");
  Serial.println(mqttClient.messageTopic());

  // use the Stream interface to print the contents
  while (mqttClient.available()) {
    msg += (char)mqttClient.read();
  }
  Serial.println(msg);

  if(topic == topic_node_sensor_relay1_set)
  {
    if(msg == "1") digitalWrite(relay1, HIGH);
    if(msg == "0") digitalWrite(relay1, LOW);
  }  

  if(topic == topic_node_sensor_relay2_set)
  {
    if(msg == "1") digitalWrite(relay2, HIGH);
    if(msg == "0") digitalWrite(relay2, LOW);
  }  

  Serial.println();
}
