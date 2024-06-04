#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>
//Define motor pin
#define motorPinRightDir  0//D2
#define motorPinRightSpeed 5//D1


Servo servo;


// Defining Wifi and Mqtt
const char* ssid = "ABBgym_2.4";
const char* password = "mittwifiarsabra";
const char* mqtt_server = "maqiatto.com";
const int mqtt_port = 1883; 
const char* mqtt_username = "gustav.sandell@hitachigymnasiet.se"; 
const char* mqtt_password = "1234"; 

WiFiClient espClient;
PubSubClient client(espClient);

// MQTT message handling
void handleMqttMessage(char* topic, byte* payload, unsigned int length) {
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  
  // Check if the payload = "W"
  if (*(char*)payload == 'W') {
    Serial.println("Received W!");
    moveForward();
    Serial.println("Forward");
    return;
  }
  // Check if the payload is "S"
  else if (*(char*)payload == 'S') {
    Serial.println("Received S!");
    moveBackwards();
    Serial.println("Backwards");
    return;
  }
   // Check if the payload is "Q"
    else if (*(char*)payload == 'Q') {
    Serial.println("Received Q!");
    Stop();
    Serial.println("Stop");
    return;
  }
  // Check if the payload is "A"
  if (*(char*)payload == 'A') {
    Serial.println("Received A!");
    TurnLeft();
    Serial.println("Turning-Left");
  }
  // Check if the payload is "D"
  else if (*(char*)payload == 'D') {
    Serial.println("Received D!");
    TurnRight();
    Serial.println("Turning-Right");
  }
}

//Conecting WiFi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected, IP address: ");
  Serial.println(WiFi.localIP());
}

// MQTT client setup
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client", mqtt_username, mqtt_password)) {
      Serial.println("connected");
      client.subscribe("gustav.sandell@hitachigymnasiet.se/WromWrom");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  //Servo and motor setup
  servo.attach(D7);
  servo.write(0);
  delay(2000);
  pinMode(motorPinRightDir, OUTPUT);
  pinMode(motorPinRightSpeed, OUTPUT);

  //Setup MQTT and Wi-Fi communication
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(handleMqttMessage);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void moveForward() {
  servo.write(75);
  // Set the direction of the motor to forward
  digitalWrite(motorPinRightDir, 1); //  1 is forward
  
  // speed 
  analogWrite(motorPinRightSpeed, 700); // 1024 is maximum speed
}

void moveBackwards() {
   servo.write(75);
  // Set the direction of the motor to backward
  digitalWrite(motorPinRightDir, 0); //-1 is backward
  
  // speed 
  analogWrite(motorPinRightSpeed, 700); // 1024 is maximum speed
}
void Stop() {
   servo.write(75);
  // Set the direction of the motor to backward
  digitalWrite(motorPinRightDir, 0); //-1 is backward
  
  // speed 
  analogWrite(motorPinRightSpeed, 0); // 1024 is maximum speed
}

void TurnLeft(){
  servo.write(0);
  Serial.println(" Left:");
}
void TurnRight(){
  servo.write(155);
  Serial.println(" Right:");
}
