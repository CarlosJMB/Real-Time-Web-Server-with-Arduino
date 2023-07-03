#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <Wire.h>
#define wifi_ssid       "YACHAYTECH"      // local router name
#define wifi_password   ""                // router password
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
String read_Temperature() {

  Wire.beginTransmission(23);
  Wire.write('T');
  Wire.endTransmission();
  Wire.requestFrom(23, 2);
  int temperature;
  temperature = Wire.read();
  temperature <<= 8;
  temperature |= Wire.read();
  Serial.print("Temperature ");
  Serial.println(temperature);
  return String(temperature);
}
String read_Humidity() {

  Wire.beginTransmission(23);
  Wire.write('H');
  Wire.endTransmission();
  Wire.requestFrom(23, 2);
  int humidity;
  humidity = Wire.read();
  humidity <<= 8;
  humidity |= Wire.read();
  Serial.print("Humidity ");
  Serial.println(humidity);
  return String(humidity);
}
String read_Pressure() {

  Wire.beginTransmission(23);
  Wire.write('P');
  Wire.endTransmission();
  Wire.requestFrom(23, 2);
  int pressure;
  pressure = Wire.read();
  pressure <<= 8;
  pressure |= Wire.read();
  Serial.print("Pressure ");
  Serial.println(pressure);
  return String(pressure);
}

void setup() {
  Serial.begin(115200);
  // Initialize SPIFFS
  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  Wire.begin();
  setup_wifi();
  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html");
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", read_Temperature().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", read_Humidity().c_str());
  });
  server.on("/pressure", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", read_Pressure().c_str());
  });
  // Start server
  server.begin();
}
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");                // here a time out could be necesary
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  delay(100);
}
