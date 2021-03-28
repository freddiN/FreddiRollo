#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

#define wifiSsid ""
#define wifiPassword ""
#define wifiHostname "Rollo_01"

#define PIN_IN1 D5
#define PIN_IN2 D6
#define PIN_IN3 D7
#define PIN_IN4 D8

unsigned int rotationSpeed = 1500;  // at least 1200

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  while(!Serial) { 
  }
  
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_IN3, OUTPUT);
  pinMode(PIN_IN4, OUTPUT);
  
  stopMotor();

  connectToWifi();

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String strDirection = "";
  String strCount = "0";

  if (server.arg("direction") != ""){
    strDirection = server.arg("direction");
  }

  if (server.arg("count") != ""){
    strCount = server.arg("count");
  }

  String HTML = "<!DOCTYPE html>\n";
  HTML += "<html>\n";
  HTML += "<head>\n";
  HTML += "<title>FreddiRollo</title>\n";
  HTML += "</head>\n";
  HTML += "<body>\n";
  HTML += "<h2>FreddiRollo</h2>\n";

  HTML += "<p>";
  HTML += "ip: ";
  HTML += WiFi.localIP().toString();
  HTML += "<br>\n";
  
  HTML += "WIFI signal: ";
  HTML += WiFi.RSSI();
  HTML += "<br>\n";

  HTML += "direction: ";
  HTML += strDirection;
  HTML += "<br>\n";

  HTML += "count: ";
  HTML += strCount;
  HTML += "<br>\n";

  HTML += "</p>\n";

  HTML += generateForm("< 256",  "left",  "256");
  HTML += generateForm("<< 1024", "left",  "1024");
  HTML += generateForm("<<< 2048", "left",  "2048");
  HTML += generateForm("<<<< 7150", "left",  "7150");
  HTML += "<br><br>";
  HTML += generateForm("> 256",  "right",  "256");
  HTML += generateForm(">> 1024", "right",  "1024");
  HTML += generateForm(">>> 2048", "right",  "2048");
  HTML += generateForm(">>>> 7150", "right",  "7150");

  HTML += "</body>\n";
  HTML += "</html>\n";

  server.send(200, "text/html", HTML);

  handleRotate(strDirection, strCount.toInt());
}

String generateForm(String strValue, String strDirection, String strCount) {
  String HTML = "";
  HTML += "<form action=\"/\" method=\"GET\">\n";
  HTML += "  <input type=\"hidden\" name=\"direction\" value=\"";
  HTML += strDirection;
  HTML += "\"/>\n";
  HTML += "  <input type=\"hidden\" name=\"count\" value=\""; 
  HTML += strCount;
  HTML += "\" />\n";
  HTML += "  <input type=\"submit\" value=\"";
  HTML += strValue;
  HTML +="\">\n";
  HTML += "</form>\n";
  return HTML;
}

void handleRotate(String strDirection, int nCount) {
  if (nCount <= 0) {
    return;
  }
  
  if (strDirection == "left") {
    for (int i=0; i<nCount; i++) {
       rotateLeft(rotationSpeed);
       yield();
    }
    stopMotor();
  } else if (strDirection == "right") {
    for (int i=0; i<nCount; i++) {
      rotateRight(rotationSpeed);
      yield();
    }
    stopMotor();
  }
}

void handleNotFound() {
  server.send(404, "text/html", "Not found");
}

void connectToWifi() {
  Serial.print("Connecting..."); 
  WiFi.hostname(wifiHostname);
  WiFi.begin(wifiSsid, wifiPassword);  
  //try to connect 20 times 0.5 seconds apart -> for 10 seconds
  int i = 20;
  while(WiFi.status() != WL_CONNECTED && i >=0) {
    delay(500);
    Serial.print(i);
    Serial.print(", ");
    i--;
  }
  Serial.println(" ");

  if(WiFi.status() == WL_CONNECTED){
    Serial.print("Connected!"); 
    Serial.println(" ");
    Serial.print("ip address: "); 
    Serial.println(WiFi.localIP());
    long rssi = WiFi.RSSI();
    Serial.print("RSSI:");
    Serial.println(rssi);
  } else {
    Serial.println("Connection failed - check your credentials or connection");
  }
}

void rotateRight(unsigned int motorSpeed) {
  // 1
  digitalWrite(PIN_IN4, HIGH);
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN1, LOW);
  delayMicroseconds(motorSpeed);

  // 2
  digitalWrite(PIN_IN4, HIGH);
  digitalWrite(PIN_IN3, HIGH);
  digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN1, LOW);
  delayMicroseconds(motorSpeed);

  // 3
  digitalWrite(PIN_IN4, LOW);
  digitalWrite(PIN_IN3, HIGH);
  digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN1, LOW);
  delayMicroseconds(motorSpeed);
  
  // 4
  digitalWrite(PIN_IN4, LOW);
  digitalWrite(PIN_IN3, HIGH);
  digitalWrite(PIN_IN2, HIGH);
  digitalWrite(PIN_IN1, LOW);
  delayMicroseconds(motorSpeed);
  
  // 5
  digitalWrite(PIN_IN4, LOW);
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN2, HIGH);
  digitalWrite(PIN_IN1, LOW);
  delayMicroseconds(motorSpeed);
  
  // 6
  digitalWrite(PIN_IN4, LOW);
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN2, HIGH);
  digitalWrite(PIN_IN1, HIGH);
  delayMicroseconds(motorSpeed);
  
  // 7
  digitalWrite(PIN_IN4, LOW);
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN1, HIGH);
  delayMicroseconds(motorSpeed);
  
  // 8
  digitalWrite(PIN_IN4, HIGH);
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN1, HIGH);
  delayMicroseconds(motorSpeed);
}

void rotateLeft(unsigned int motorSpeed) {
  
  // 1
  digitalWrite(PIN_IN1, HIGH);
  digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN4, LOW);
  delayMicroseconds(motorSpeed);
  
  // 2
  digitalWrite(PIN_IN1, HIGH);
  digitalWrite(PIN_IN2, HIGH);
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN4, LOW);
  delayMicroseconds(motorSpeed);

  // 3
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, HIGH);
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN4, LOW);
  delayMicroseconds(motorSpeed);
  
  // 4
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, HIGH);
  digitalWrite(PIN_IN3, HIGH);
  digitalWrite(PIN_IN4, LOW);
  delayMicroseconds(motorSpeed);
  
  // 5
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN3, HIGH);
  digitalWrite(PIN_IN4, LOW);
  delayMicroseconds(motorSpeed);
  
  // 6
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN3, HIGH);
  digitalWrite(PIN_IN4, HIGH);
  delayMicroseconds(motorSpeed);
  
  // 7
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN4, HIGH);
  delayMicroseconds(motorSpeed);
  
  // 8
  digitalWrite(PIN_IN1, HIGH);
  digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN4, HIGH);
  delayMicroseconds(motorSpeed);
}

void stopMotor() {
    digitalWrite(PIN_IN4, LOW);
    digitalWrite(PIN_IN3, LOW);
    digitalWrite(PIN_IN2, LOW);
    digitalWrite(PIN_IN1, LOW);
}
