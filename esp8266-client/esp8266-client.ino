#include <ESP8266WiFi.h>
#include <WebSocketClient.h>
#include <SPI.h>
#include <MFRC522.h>

/* wiring the MFRC522 to ESP8266 (ESP-12)
RST     = GPIO5
SDA(SS) = GPIO4 
MOSI    = GPIO13
MISO    = GPIO12
SCK     = GPIO14
GND     = GND
3.3V    = 3.3V
*/

#define RST_PIN  5  // RST-PIN for RC522 - RFID - SPI - Modul GPIO5 
#define SS_PIN  4  // SDA-PIN for RC522 - RFID - SPI - Modul GPIO4 

const char* ssid     = "Thundercats";
const char* password = "***";
char *path = "/";
char *host = "192.168.0.121";
const int port = 8080;

MFRC522 nfc(SS_PIN, RST_PIN);  
WebSocketClient webSocketClient;
WiFiClient client;

byte foundTag; // Variable used to check if Tag was found
byte readTag; // Variable used to store anti-collision value to read Tag information
byte tagData[MAX_LEN]; // Variable used to store Full Tag Data
byte tagSerialNumber[4]; // Variable used to store only Tag Serial Number

void setup() {
  Serial.begin(115200);
  
  nfc.begin();
  SPI.begin();           // Init SPI bus
  WiFi.begin(ssid, password);  
  
  int retries = 0;
  
  while ((WiFi.status() != WL_CONNECTED) && (retries < 10)) {
    retries++;
    delay(500);
    Serial.print(".");
  }
  
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected");
  }
}

void connectToServer()
{  
  while(!client.connect(host, port)) 
  {
    delay(500);
  }

  // Handshake with the server
  webSocketClient.path = path;
  webSocketClient.host = host;
  
  while(!webSocketClient.handshake(client)) 
  {
    delay(500);
  }
}

bool disconnectFromServer()
{
  client.stop();
}

void loop() 
{
  foundTag = nfc.requestTag(MF1_REQIDL, tagData);
    delay(1);

    if (foundTag != MI_OK)
        return ; 

  // Get anti-collision value to properly read information from the Tag
    readTag = nfc.antiCollision(tagData);
    memcpy(tagSerialNumber, tagData, 4); // Write the Tag information in the tagSerialNumber variable
  String data((char *)tagData);
  
  connectToServer();
  delay(250);
  webSocketClient.sendData(data);
  delay(250);
  disconnectFromServer();
}
