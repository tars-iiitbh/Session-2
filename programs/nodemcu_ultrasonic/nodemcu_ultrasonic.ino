#include <ESP8266WiFi.h>

const int trigPin = 13;  //D7
const int echoPin = 12;  //D6

long duration=0;
long distance=0;

char ssid[] = "Redmi";    
char pass[] = "detroitsmash";

WiFiClient client;

void setup() {
  Serial.println( "okay!");
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(115200);
  
  Serial.println("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, pass);
       
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
      
  Serial.println("");
  Serial.println("WiFi connected");
}
 
void loop(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.println(distance);
  if (WiFi.status() == WL_CONNECTED){
    Serial.print("Distance: ");
    Serial.println(distance);
    delay(500);
  }       
  else{
    Serial.println("Waiting...");
  }
}





 
