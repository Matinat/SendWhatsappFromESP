#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASS"
const String YOUR_PHONE = "5490000000000"; //Without +
const String YOUR_APIKEY = "12345678"; //Your API KEY
const String URL = "http://api.whatabot.net//whatsapp/sendMessage?text=";
WiFiUDP ntpUDP;

void setup() {
  wifiConnect();
  //Use the URL encoded blackspace (%20)
  sendWhatsapp("Hello%20from%20esp8266");
}

void sendWhatsapp(String text) {
  WiFiClient client;
  HTTPClient https;
  String url = URL + text + "&apikey=" + YOUR_APIKEY + "&phone=" + YOUR_PHONE;
  https.begin(client, url);
  int httpCode = https.GET();
  https.end();
}


void loop() {

}

void wifiConnect() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  Serial.println(" ...");
  byte teller = 0;
  while (WiFi.status() != WL_CONNECTED) {  // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++teller);
    Serial.print(' ');
    if (teller % 40 == 0) {
      teller = 0;
      Serial.println();
    }
  }
  Serial.println('\n');
  Serial.println("Connection established");
  Serial.print("IP address: \t");
  Serial.println(WiFi.localIP());
}
