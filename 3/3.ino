/*This program creates a webserver and a websocket server.
 * Writing the coman on or off in the website will change 
 * the state of the led.
 *
 *Esquematics are apresented in this folder with the 
 *same name as the code file(they work both on arduino 
 *and nodemcu).
 *
 *
 *Made by: Diogo Valdrez
 *Setember 2021
 *
 *https://github.com/DiogoValdrez
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <Hash.h>

#define LED D2

const char* ssid = "TP-LINK_43CC";
const char* password = "80087816";

const char* keyword = "on";
const char* keyword2 = "off";
int ledvalue = 0;

String WebPage = "<!DOCTYPE html><html><style>input[type=\"text\"]{width: 90%; height: 3vh;}input[type=\"button\"]{width: 9%; height: 3.6vh;}.rxd{height: 90vh;}textarea{width: 99%; height: 100%; resize: none;}</style><script>var Socket;function start(){Socket=new WebSocket('ws://' + window.location.hostname + ':81/'); Socket.onmessage=function(evt){document.getElementById(\"rxConsole\").value +=evt.data;}}function enterpressed(){Socket.send(document.getElementById(\"txbuff\").value); document.getElementById(\"txbuff\").value=\"\";}</script><body onload=\"javascript:start();\"> <div><input class=\"txd\" type=\"text\" id=\"txbuff\" onkeydown=\"if(event.keyCode==13) enterpressed();\"><input class=\"txd\" type=\"button\" onclick=\"enterpressed();\" value=\"Send\" > </div><br><div class=\"rxd\"> <textarea id=\"rxConsole\" readonly></textarea> </div></body></html>";

WebSocketsServer webSocket = WebSocketsServer(81);
ESP8266WebServer server(80);

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
   }
    
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.on("/", [](){
    server.send(200, "text/html", WebPage);
    });
    
    server.begin();
    
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
}

void loop() {
    webSocket.loop();
    server.handleClient();
    if (Serial.available() > 0){
      char c[] = {(char)Serial.read()};
      webSocket.broadcastTXT(c, sizeof(c));
    }
    if(ledvalue == 1) {
      digitalWrite(LED, HIGH);
    
    } else {
      digitalWrite(LED, LOW);
    }
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
   if (type == WStype_TEXT){
    for(int i = 0; i < length; i++) Serial.print((char) payload[i]);
    Serial.println();
    if (length == 2 && *(char*) payload == *keyword && *(char*) (payload + sizeof(char)) == *(keyword + sizeof(char))){
      char c[] = "Led turned ON\n";
      webSocket.broadcastTXT(c, sizeof(c));
      Serial.println(c);
      
      ledvalue = 1;
    }else if(length == 3 && *(char*) payload == *keyword2 && *(char*) (payload + sizeof(char)) == *(keyword2 + sizeof(char)) 
    && *(char*) (payload + sizeof(char)+ sizeof(char)) == *(keyword2 + sizeof(char)+ sizeof(char))){
      char c[] = "Led turned OFF\n";
      webSocket.broadcastTXT(c, sizeof(c));
      Serial.println(c);
      ledvalue = 0;
    }
  }
}
