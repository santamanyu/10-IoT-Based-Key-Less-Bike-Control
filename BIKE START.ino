#include <ESP8266WiFi.h>
 
const char* ssid = "santa";			//YOUR WIFI USER NAME
const char* password = "santamanyu";		//YOUR WIFI PASSWORD
 
int Relay1 = 5;   //D1
int Relay2 = 4;   //D2
int Relay3 = 0;   //D3
int Relay4 = 2;   //D4
int choice = 0;

WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(Relay1, OUTPUT);
  digitalWrite(Relay1, LOW);
  pinMode(Relay2, OUTPUT);
  digitalWrite(Relay2, LOW);
    
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
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
 
void loop() {

//pattern for indicator light
switch (choice)
  {
	case 0:
  digitalWrite(Relay3, LOW);
  digitalWrite(Relay4, LOW);
    break;
    case 1:
  digitalWrite(Relay3, HIGH);
  digitalWrite(Relay4, HIGH);
  delay(500);
  digitalWrite(Relay3, LOW);
  digitalWrite(Relay4, LOW);
  delay(500);
  break;
  case 2:
  digitalWrite(Relay3, HIGH);
  delay(500);
  digitalWrite(Relay3, LOW);
  digitalWrite(Relay4, HIGH);
  delay(500);
  digitalWrite(Relay4, LOW);
  }
  
 // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
 // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  
  // Match the request
  if (request.indexOf("/RELAY1=ON") != -1)  {
    digitalWrite(Relay1, HIGH);
  }
  if (request.indexOf("/RELAY1=OFF") != -1)  {
    digitalWrite(Relay1, LOW);
   }
  if (request.indexOf("/RELAY2=ON") != -1)  {
  digitalWrite(Relay2, HIGH);
  delay(500);
  digitalWrite(Relay2, LOW);
   }
   //indicators
  if (request.indexOf("/RELAY3=OFF") != -1)  {
  choice=0;
  }
  if (request.indexOf("/RELAY3=ON") != -1)  {
  choice=1;
  }
  if (request.indexOf("/RELAY4=ON") != -1)  {
  choice=2;
  }
  
   
  
    // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<body align=center background=http://www.walldevil.com/wallpapers/a87/pattern-texture-light-background-wallpaper-flower-image.jpg width=1202 height=1206>"); 
  client.println("<br><font size=7><b>MY BIKE CONTROL</b></font>");
  client.print("<h1>       -by SANTAMANYU </h1>");
  client.println("<img src=https://lh3.googleusercontent.com/-Xmm9eDnFt3Y/AAAAAAAAAAI/AAAAAAAAAA0/JlT9RRqzEJw/photo.jpg?sz=50 width=202 height=206 border=5 /><br/>");
  client.println("<br><a href=\"/RELAY1=ON\"\"><button style=height:200px;width:400px;color:green;border-radius:100px;><h1> IGNITION ON</h1></button></a>");
  client.println("<a href=\"/RELAY1=OFF\"\"><button style=height:200px;width:400px;color:red;border-radius:100px;><h1>IGNITION OFF</h1> </button></a><br />");  
  client.println("<br><a href=\"/RELAY2=ON\"\"><button style=height:200px;width:800px;color:green;border-radius:100px;><h1> BIKE START</h1></button></a>");
  client.println("<br><a href=\"/RELAY3=ON\"\"><button style=height:200px;width:400px;color:green;border-radius:100px;><h1> INDICATORS ON</h1></button></a>");
  client.println("<a href=\"/RELAY3=OFF\"\"><button style=height:200px;width:400px;color:red;border-radius:100px;><h1>INDICATORS OFF</h1> </button></a>");  
  client.println("<br><a href=\"/RELAY4=ON\"\"><button style=height:200px;width:400px;color:green;border-radius:100px;><h1> INDICATORS patterns</h1></button></a><br />");
  
  client.println("</body>");
  client.println("</html>"); 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
