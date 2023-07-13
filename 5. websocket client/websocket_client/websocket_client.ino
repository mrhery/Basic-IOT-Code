#include <ESP8266WiFi.h>
#include <WebSocketClient.h>

const char* ssid     = "Sally2.4@unifi";
const char* password = "SalmaH1234567";
#define RELAY 0

WebSocketClient ws(true);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  pinMode(RELAY,OUTPUT);
  digitalWrite(RELAY, LOW);
}

void loop() {
  int value = LOW;
  // put your main code here, to run repeatedly:
  if (!ws.isConnected()) {
    ws.connect("offwork.online", "/echo/thing/rumah_mak/lampuBilikMak1", 55888);
  } else {
    //ws.send("hello");

    String msg;
    if (ws.getMessage(msg)) {
      if(getValue(msg, ':', 0) == "status"){
        ws.send(String("{\"action\": \"status\", \"to\": \""+ String(getValue(msg, ':', 1)) +"\", \"data\": \""+ String(value) +"\"}"));
        
        Serial.println(String("{\"action\": \"status\", \"to\": \""+ String(getValue(msg, ':', 1)) +"\", \"data\": \""+ String(value) +"\"}"));
      }else if(getValue(msg, ':', 0) == "on"){
        digitalWrite(RELAY,LOW);
        value = LOW;

        ws.send(String("{\"action\": \"status\", \"to\": \""+ String(getValue(msg, ':', 1)) +"\", \"data\": \""+ String(value) +"\"}"));
        
        Serial.println(String("{\"action\": \"status\", \"to\": \""+ String(getValue(msg, ':', 1)) +"\", \"data\": \""+ String(value) +"\"}"));
      }else if (getValue(msg, ':', 0) == "off"){
        digitalWrite(RELAY,HIGH);
        value = HIGH;

        ws.send(String("{\"action\": \"status\", \"to\": \""+ String(getValue(msg, ':', 1)) +"\", \"data\": \""+ String(value) +"\"}"));
        
        Serial.println(String("{\"action\": \"status\", \"to\": \""+ String(getValue(msg, ':', 1)) +"\", \"data\": \""+ String(value) +"\"}"));
      }
      //Serial.println(getValue(msg, ':', 0));
      //Serial.println(getValue(msg, ':', 1));
    }
  }
  delay(500);
}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
