#include <Blynk.h>

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


// defines pins numbers
const int trigPin = 13;  //D7
const int echoPin = 12;  //D6

// defines variables
long duration=0;
int distance=0;

SimpleTimer timer;
char auth[] = "1c821ad4ce7c4330b7a959fa98672c40";
char ssid[] = "Redmi";
char pass[] = "detroitsmash";

void enterVal(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.println(distance);
  Blynk.virtualWrite(V0 , distance);
}

void setup(){
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(2000, enterVal);
}
void loop()
{
  Blynk.run();
  timer.run();
}

