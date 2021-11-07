#include <Adafruit_BME280.h>
#include <WiFi.h>
#include <Wire.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Adafruit_NeoPixel.h>

const char* ssid = "Tomato24";
const char* password = "";
const int PIN = 8;

WebServer server(80);
Adafruit_NeoPixel pixels(1, PIN, NEO_GRB + NEO_KHZ800);
BME280 mySensor;

void handleRoot() {
  pixels.setPixelColor(0, pixels.Color(0, 254, 0));
  pixels.show();   // Send the updated pixel colors to the hardware.
  server.send(200, "text/plain", "hello from esp32!");
  pixels.setPixelColor(0, pixels.Color(0, 0, 254));
  pixels.show();   // Send the updated pixel colors to the hardware.
}

void handleMetrics() {
  Serial.println("handleMetrics recevied");
  pixels.setPixelColor(0, pixels.Color(254, 0, 0));
  pixels.show();   // Send the updated pixel colors to the hardware.

  // humidity    = mySensor.readFloatHumidity();
  // pressure    = mySensor.readFloatPressure();
  // temperature = mySensor.readTempC();

  Serial.println("constructing response");
  String message = "humidity: ";
  message += mySensor.readFloatHumidity();
  message += "\npressure: ";
  message += mySensor.readFloatPressure();
  message += "\ntemperature: ";
  message += mySensor.readTempC();
  message += "\n";
  Serial.println("sending response");
  server.send(200, "text/plain", message);
  pixels.setPixelColor(0, pixels.Color(0, 0, 254));
  pixels.show();   // Send the updated pixel colors to the hardware.
  Serial.println("handleMetrics done");
}

void handleNotFound() {
  pixels.setPixelColor(0, pixels.Color(0, 254, 0));
  pixels.show();   // Send the updated pixel colors to the hardware.
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  pixels.setPixelColor(0, pixels.Color(0, 0, 254));
  pixels.show();   // Send the updated pixel colors to the hardware.
}

void setup(void) {
  Serial.begin(115200);
  Serial.println("setup wire");
  Wire.begin(0,1);
  mySensor.setI2CAddress(0x77);
  mySensor.beginI2C()
  Serial.println("setup wire");
  
  Serial.println("setup pixel");
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear(); // Set all pixel colors to 'off'
  Serial.println("done pixel");
  
  Serial.println("setup wifi");
  WiFi.mode(WIFI_STA);
  //WiFi.begin(ssid, password);
  WiFi.begin(ssid, NULL);
  Serial.println("done wifi");

  // Wait for connection
  Serial.println("wait for wifi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/metrics", handleMetrics);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  Serial.println("web server begin");
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks
}
