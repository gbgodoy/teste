#include <ESP8266WiFi.h>    
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "VIVO-D179";
const char *password = "2F8A23D179";

String CardID="";
String payload="";
String getData ,Link;


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting to ");
  Serial.print(ssid);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.println("Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

void loop() {
  if(WiFi.status() != WL_CONNECTED){
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    Serial.print("Reconnecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("Connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
	HTTPClient http;
	//GET
	getData = "?CardID=" + CardID;
	Link = "http://www.euboton.com.br/envio.php" + getData;

	http.begin(Link);

	int httpCode = http.GET();            //Send the request
	delay(10);
	String payload = http.getString();    //Get the response payload

	Serial.println(httpCode);   //Print HTTP return code
	Serial.println(payload);    //Print request response payload
	Serial.println(CardID);     //Print Card ID
  delay(500);
  
  CardID = "";
  getData = "";
  Link = "";
  http.end();  //Close connection
}
