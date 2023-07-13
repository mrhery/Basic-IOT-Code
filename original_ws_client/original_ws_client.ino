#include <Arduino.h>
#include "WebSocketClient.h"
#include "ESP8266WiFi.h"

WebSocketClient ws(false);

void setup() {
  Serial.begin(115200);
  WiFi.begin("mrhery1", "heryheryhery");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

void loop() {
  if (!ws.isConnected()) {
    Serial.println("Try to connect...");
    ws.connect("myaims.com.my", "/echo/", 55888);

    delay(3000);
  } else {
    //ws.send("hello");

    String msg;
    if (ws.getMessage(msg)) {
      Serial.println(msg);
    }
  }
  delay(500);
}
