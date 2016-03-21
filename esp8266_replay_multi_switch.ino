// Switch control using the ESP8266 WiFi chip

// Import required libraries
#include <ESP8266WiFi.h>
#include <aREST.h>
#include <aREST_UI.h>

// Create aREST instance
aREST_UI ui = aREST_UI();

// WiFi SSID/password
const char* ssid = "wifissid";
const char* password = "wifipassword";

// Update these with values suitable for your network.
IPAddress ip(<staticIp>);  //Node static IP. replace <> with ip address
IPAddress gateway(<gateway>); //wifi gateway
IPAddress subnet(<subnet>); //wifi subnet

// The port to listen for incoming TCP connections
#define LISTEN_PORT           80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);
void setup(void)
{
  // Start Serial
  Serial.begin(115200);

  // Create UI
  ui.title("Switch Control");
  
//1st button connected to GPIO5
  ui.label("button1");
  ui.button(5);

//2nd button connected to GPIO4
  ui.label("button2");
  ui.button(4);

  // Give name and ID to device
  ui.set_id("1");
  ui.set_name("esp8266");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);

  //Wifi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());

}

void loop() {

  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while (!client.available()) {
    delay(1);
  }
  ui.handle(client);

}
