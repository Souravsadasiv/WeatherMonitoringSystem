// #include <ESP8266WiFi.h>
 
// const char* ssid = "SOURAV"; // Replace with your network name
// const char* password = "12345678"; // Replace with your network password
 
// WiFiServer server(80); // Create a web server on port 80
 
// void setup() {
//   Serial.begin(9600);
//   delay(10);

//   // Connect to Wi-Fi network
//   Serial.println();
//   Serial.println();
//   Serial.print("Connecting to ");
//   Serial.println(ssid);
 
//   WiFi.begin(ssid, password);
 
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
 
//   Serial.println("");
//   Serial.println("WiFi connected");
 
//   // Start the server
//   server.begin();
//   Serial.println("Server started");
// }
 
// void loop() {
//   // Check if a client has connected
//   WiFiClient client = server.available();
//   if (!client) {
//     return;
//   }
 
//   // Wait until the client sends some data
//   Serial.println("new client");
//   while (!client.available()) {
//     delay(1);
//   }
 
//   // Read the first line of the request
//   String request = client.readStringUntil('\r');
//   Serial.println(request);
//   client.flush();
 
//   // Send the response to the client
//   client.println("HTTP/1.1 200 OK");
//   client.println("Content-Type: text/html");
//   client.println("");
//   client.println("<html><body>");
//   client.println("<h1>Hello World!</h1>");
//   client.println("</body></html>");
//   delay(1);
//   Serial.println("Client disonnected");
// }

// #include <ESP8266WiFi.h>
// #include <WiFiClient.h>
// #include <ESP8266WebServer.h>
// #include <SoftwareSerial.h>

// SoftwareSerial softSerial(5, 4);  // RX, TX pins for ESP8266 communication
// ESP8266WebServer server(80);

// const char* ssid = "SOURAV";
// const char* password = "12345678";
// IPAddress ip(192, 168, 1, 111);   // IP address of the ESP8266 module
// IPAddress gateway(192, 168, 1, 1);
// IPAddress subnet(255, 255, 255, 0);

// void handleSensorData() {
//   float temperature = 0;
//   float humidity = 0;

//   // Connect to the Arduino board
//   softSerial.begin(9600);
//   while (!softSerial) {}

//   // Read DHT sensor data from the Arduino board
//   softSerial.print("R");
//   temperature = softSerial.parseFloat();
//   humidity = softSerial.parseFloat();
//   softSerial.flush();

//   // Send the DHT sensor data to the client
//   String response = String(temperature) + "," + String(humidity);
//   server.send(200, "text/plain", response);
// }

// void setup() {
//   Serial.begin(115200);
//   delay(10);

//   // Connect to Wi-Fi
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.println("Connecting to WiFi...");
//   }

//   // Set the IP address of the ESP8266 module
//   WiFi.config(ip, gateway, subnet);

//   Serial.println("WiFi connected");
//   Serial.println("IP address: ");
//   Serial.println(WiFi.localIP());

//   // Serve the sensor data on the server
//   server.on("/sensor_data", handleSensorData);

//   server.begin();
//   Serial.println("Server started");
// }

// void loop() {
//   server.handleClient();
// }
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <dht11.h>

// Define the pin for the DHT sensor
#define DHTPIN D1

// Define the type of DHT sensor (DHT11 or DHT22)
#define DHTTYPE DHT11

// Initialize the DHT sensor
dht11 dht(DHTPIN, DHTTYPE);

// Replace with your network credentials
const char* ssid = "SOURAV";
const char* password = "12345678";

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "Hello World!");
}

void handleSensor() {
  // Read the temperature and humidity from the DHT sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Return the temperature and humidity in the HTTP response
  String message = "Temperature: " + String(temperature) + " C\nHumidity: " + String(humidity) + " %";
  server.send(200, "text/plain", message);
}

void setup() {
  // Initialize the serial port and DHT sensor
  Serial.begin(9600);
  dht.begin();

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for Wi-Fi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Start the web server
  server.on("/", handleRoot);
  server.on("/sensor", handleSensor);
  server.begin();
}

void loop() {
  // Listen for incoming HTTP requests
  server.handleClient();
}

