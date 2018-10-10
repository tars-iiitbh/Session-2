#include <ESP8266WiFi.h>

const int trigPin = 13;  //D7
const int echoPin = 12;  //D6

long duration=0;
int distance=0;

String apiKey = "1SO04H5ESINTUQ0H";    
const char *ssid =  "leviackerman";     
const char *pass =  "q1w2r4t5";
const char* server = "api.thingspeak.com";

WiFiClient client;

void setup(){
  Serial.println( "okay!");
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(115200);
   
  Serial.println("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, pass);
 
  while (WiFi.status() != WL_CONNECTED) {
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
  if (client.connect(server,80)){
    
    String postStr = apiKey;
    postStr +="&field1=";
    postStr += String(distance);
    postStr += "\r\n\r\n";
 
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
 
    Serial.print("Distance ");
    Serial.print(distance);
                             
    Serial.println(" Send to Thingspeak.");
  }
                       
  client.stop();
  Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
  delay(1500);
}
