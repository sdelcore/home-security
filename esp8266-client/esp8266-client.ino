#include <ESP8266WiFi.h>
#include <WebSocketClient.h>

const char* ssid     = "Thundercats";
const char* password = "92sd94gd";
char *path = "/";
char *host = "192.168.0.162";
const int port = 8080;
  
WebSocketClient webSocketClient;
WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);  
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
  }
}

String readFromSerial(int num)
{
  String incoming = String();
  
  if(Serial.available() >= num)
  {
    for(int i = 0; i < num; i++)
    {
      incoming += Serial.read();
    }
  }

  return incoming;
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
  
  while(!webSocketClient.handshake(client)) {
    delay(500);
  }
}

bool disconnectFromServer()
{
  client.stop();
}

void loop() 
{
  delay(1000);
  
  if(Serial.available() <= 7)
    return;

  connectToServer();
  String data = readFromSerial(7);  
  webSocketClient.sendData(data);
  disconnectFromServer();
}
