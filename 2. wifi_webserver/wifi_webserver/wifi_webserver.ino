#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "mrhery1";
const char* password = "heryheryhery";

//IPAddress local_ip(192,168,43,95);
//IPAddress gateway(192,168,43,1);
//IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println("\n");
  WiFi.begin(ssid, password);             // Connect to the network
  //WiFi.softAP(ssid, password);
  //WiFi.softAPConfig(local_ip, gateway, subnet);
  
  //Serial.print("Connecting to ");
  //Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print('.'); Serial.print(' ');
  }

  Serial.println('\n'); 
  Serial.print("Server IP address:\t");
  Serial.println(WiFi.localIP()); 

  server.on("/", homepage);
  server.on("/page1", page1);
  server.onNotFound(notfound);

  server.begin();
}

void loop() {
  server.handleClient();
}

void notfound(){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>Not Found Page</h1>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";

  server.send(200, "text/html", ptr);
}
void homepage(){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>Home Page</h1>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";

  server.send(200, "text/html", ptr);
}

void page1(){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>Page 1</h1>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";

  server.send(200, "text/html", ptr);
}
