#include <ESP8266WiFi.h>

const char* ssid = "mrhery1";
const char* password = "heryheryhery";

void setup() {
  WiFi.begin(ssid, password);

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }
  
}

void loop() {

}
