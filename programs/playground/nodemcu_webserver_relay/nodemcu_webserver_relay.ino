#include <ESP8266WiFi.h>

const char* ssid     = "leviackerman";
const char* password = "q1w2r4t5";

WiFiServer server(80); //HTTP Request

String header;
String output5State = "off";
const int output5 = 5;//D1

void setup() {
  Serial.begin(115200);
  pinMode(output5, OUTPUT);
  digitalWrite(output5, LOW);
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available(); 

  if (client) {                             
    Serial.println("New Client.");          
    String currentLine = "";                
    
    while (client.connected()){            
      if (client.available()){             
        
        char c = client.read();
        header += c;
        
        if (c == '\n') {
          
          if (currentLine.length() == 0) {
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /5/on") >= 0) {
              output5State = "on";
              digitalWrite(output5, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              output5State = "off";
              digitalWrite(output5, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            
            // Display current state, and ON/OFF buttons for GPIO 5  
            client.println("<p>State Ready to Switch To : " + output5State + "</p>");
            // If the output5State is off, it displays the ON button       
            if (output5State=="off") {
              client.println("<p><a href=\"/5/on\"><button>SWITCH IS ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button>SWITCH IS OFF</button></a></p>");
            } 
               
            client.println("</body></html>");
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r'){
          currentLine += c;  
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    Serial.println("Session Closed.");
  }
}
