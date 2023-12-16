#include <ESP8266WiFi.h>

// based on: https://www.instructables.com/ESP0101S-RELAY-MODULE-TUTORIAL/ 
// https://arduino-esp8266.readthedocs.io/en/3.0.1/esp8266wifi/readme.html
// https://arduino-esp8266.readthedocs.io/en/3.0.1/esp8266wifi/generic-class.html
// 
// This example is fragile and stops working. 
// One comment recommended: - https://github.com/me-no-dev/ESPAsyncWebServer/ 

#include "relayExample_my_ssid_password.h"

#define RELAY 0 // relay connected to  GPIO0
#define RELAY2 2 // relay connected to  GPIO2

WiFiServer server(80);
 
void setup() 
{
  Serial.begin(115200); // must be same baudrate with the Serial Monitor
 
  pinMode(RELAY,OUTPUT);
  pinMode(RELAY2,OUTPUT);

  digitalWrite(RELAY, LOW);
  digitalWrite(RELAY2, LOW);
  delay(250);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}

  int value = LOW;

 
void loop() 
{
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) 
  {
    return;
  }
 
  // Wait until the client sends some data
  //  Serial.println("new client");

  
  while(!client.available())
  {
    delay(1);
    // increase delay
    delay(100);
  }
  Serial.println("new client");
  delay(100);


  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
//  int value = LOW;
  if (request.indexOf("/RELAY=ON") != -1)  
  {
    Serial.println("RELAY=ON");
    // holdoff the relay untill after the webpage
    //digitalWrite(RELAY,LOW);
    //digitalWrite(RELAY2,LOW);
    value = LOW;
    
  }
  if (request.indexOf("/RELAY=OFF") != -1)  
  {
    Serial.println("RELAY=OFF");
    //digitalWrite(RELAY,HIGH);
    //digitalWrite(RELAY2,HIGH);
    value = HIGH;
    
  }
  if (request.indexOf("/favicon.ico") != -1){
    // for now returun 404 
    client.println("HTTP/1.1 404 Not Found");  
  } else {
    // Return the response
    client.println("HTTP/1.1 200 OK");
  }
  
  // Return the response
  //client.println("HTTP/1.1 200 OK");

  client.println("Content-Type: text/html");
  client.println(""); //  this is a must. It 
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><title>ESP8266 RELAY Control</title></head>");
  client.println("<style>");
  client.println("h2 {color:; font-family: Arial, Helvetica, sans-serif;  }");
  client.println("body { color:Tomato;    }");
  client.println("a    { color:SlateBlue; }");
  client.println("</style>" );
  
  client.print("<h2>Relay is now: ");

/*
 * Inline graphics produced using paint and https://www.w3docs.com/tools/image-base64
 */
 
  if( value == HIGH) 
  {
    client.print("OFF <BR>");
    // inline png red square
    client.print("<img src=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAIAAAD8GO2jAAAAAXNSR0IArs4c6QAAAARnQU1BAACxjwv8YQUAAAAJcEhZcwAAFiUAABYlAUlSJPAAAABISURBVEhL7c2hEQAhDAVRCkHSf2fUkBNhBrkm4czuRET9N6K5V8Ceq/xy+QL5VCWACWACmAAmgAlgApgA9gdQfrl8gL6agYgP3pQw5nia0O4AAAAASUVORK5CYII=\" />");

  } 
  else 
  {
    client.print("ON <BR>");
    // inline png green square
    client.print("<img src=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAIAAAD8GO2jAAAAAXNSR0IArs4c6QAAAARnQU1BAACxjwv8YQUAAAAJcEhZcwAAFiUAABYlAUlSJPAAAABNSURBVEhLY/z//z8DLQETlKYZgPpg23M5CJ+KwEvyEZCkuQ9GLSAIRi0gCEYtIAhGLSAIRi0gCEYtIAhGLSAIRi0gCIa+BUO9dc3AAACG8ww11iOlOgAAAABJRU5ErkJggg==\" />");
  
  }
  client.println("</H2>");
  client.println("<h2>Turn <a href=\"/RELAY=OFF\">OFF</a> RELAY</H2>");
  client.println("<h2>Turn <a href=\"/RELAY=ON\">ON</a> RELAY</H2>");
  
  client.println("</html>");
  //client.flush();
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");

  digitalWrite(RELAY, value);
  digitalWrite(RELAY2,value);
}
