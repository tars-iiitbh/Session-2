#include <ArduinoJson.h>

#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>

#include <ESP8266WiFi.h>

const int trigPin = 13;  //D7
const int echoPin = 12;  //D6

long duration=0;
long distance=0;

#define FIREBASE_HOST "https://plus-ultra-b2896.firebaseio.com"
#define FIREBASE_AUTH "yqjOEGnfJqZdk4P5zOj0FOseHa26GsGYxNzQ3Qcy"

#define WIFI_SSID "leviackerman"
#define WIFI_PASSWORD "q1w2r4t5"

void setup() {
  Serial.println( "okay!");
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(115200);
  
  Serial.println("Connecting to ");
  Serial.println(WIFI_SSID);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

Serial.println();
Serial.print("connected: ");

Serial.println(WiFi.localIP());

Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
Firebase.setInt("distance",0);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  if(WiFi.status() == WL_CONNECTED){
    Serial.print("Distance: ");
    Firebase.setInt("distance",0);
    Serial.println(distance);
    delay(500);
  }
  else{
    Serial.println("Waiting...");
  }

  if (Firebase.failed()){
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
  }
  delay(1000);
}
