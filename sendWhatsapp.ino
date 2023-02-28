#define USING_AXTLS
#include <ESP8266WiFi.h>
#include <WiFiClientSecureAxTLS.h>
using namespace axTLS;

#ifndef STASSID
#define STASSID "YOUR_SSID"
#define STAPSK  "YOUR_PASS"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const char* host = "api.whatabot.net";
const int httpsPort = 443;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored  "-Wdeprecated-declarations"
WiFiClientSecure client;
#pragma GCC diagnostic pop

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Connect to remote server
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  String url = "/whatsapp/sendMessage?apikey=12345678&text=Hello&phone=5490000000000";
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +            
               "Connection: close\r\n\r\n");

  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
 
  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println();

  static int repeat = 0;
  if (++repeat == 2) {
    Serial.println("Done");
    while (true) {
      delay(1000);
    }
  }
  delay(10000);
}
