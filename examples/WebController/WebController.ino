#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "my_OIS.h"
#include "website.h"

const char* ssid = "ssid";
const char* pass = "password";

const int CHANNELS = 1;
Controller controller(CHANNELS);
bool flag[CHANNELS];//used to tell when something updates

ESP8266WebServer server(80);

void handleroot(){
  //Serial.println("root");
  server.send(200,"",webpage);
}

void handleNotFound(){
 
  String message = "File Not Found\n\n";
  //Serial.print(message);
  String com = server.arg("com");
  if(-1 != com.indexOf("burn")){
    //Serial.println("burn");
    controller.exc(0);
  }
}


void setup() {
  // put your setup code here, to run once:
  controller.add(0,Comm("CMD","TOGGLE_MAIN_ENGINE",0));
  for(int i=0;i<CHANNELS; ++i)
    flag[i]=false;
  Serial.begin(9600);
  WiFi.begin(ssid,pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
  MDNS.begin("controller");

  server.on("/",handleroot);

  server.onNotFound(handleNotFound);
  
  server.begin();

  Handshake();

  controller.sync();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}

