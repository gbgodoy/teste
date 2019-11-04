  #include <EEPROM.h>
	#include <ESP8266WiFi.h>    
  #include <WiFiClient.h> 
  #include <ESP8266WebServer.h>
  #include <ESP8266HTTPClient.h>
  #include <SPI.h>
  #include <MFRC522.h>     
  #include <Wire.h>
  #include <LiquidCrystal_I2C.h>

  #define SS_PIN 53
  #define RST_PIN 49
  #define pirPin 7
  #define ledPin 3
	#define but1Pin 23	//compra1
	#define but1Pin 24	//compra2
	#define but1Pin 25	//compra3
	#define but1Pin 26	//compra4
	#define but1Pin 27	//compra5

	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, OUTPUT);
	pinMode(relePin, OUTPUT);
	pinMode(but1Pin, INPUT_PULLUP);
	pinMode(but2Pin, INPUT_PULLUP);
	pinMode(but3Pin, INPUT_PULLUP);
	pinMode(but4Pin, INPUT_PULLUP);
	pinMode(but5Pin, INPUT_PULLUP);

  MFRC522 mfrc522(SS_PIN, RST_PIN);
  LiquidCrystal_I2C lcd(0x27, 16, 2);

  const char *ssid = "SSID";
  const char *password = "password";

  const char *host = "192.168.x.x";

  String getData ,Link;
  String CardID="";

  void setup() {
  	mensageminicial();
    delay(1000);
    Serial.begin(115200);
    SPI.begin();  // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522 card

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

    pinMode(RedLed,OUTPUT);
    pinMode(BlueLed,OUTPUT);
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
    
    if ( mfrc522.PICC_IsNewCardPresent()) {
      if ( mfrc522.PICC_ReadCardSerial()) {
        Serial.print("UID da Tag:");
        for (byte i = 0;i < mfrc522.uid.size; i++){
          CardID += mfrc522.uid.uidByte[i];
          Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
          Serial.print(mfrc522.uid.uidByte[i], HEX);
        }
        Serial.println();
        mfrc522.PICC_HaltA();  
      }
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
    
    if (payload == "liberado"){
      nemas();
      delay(500);  //Post Data at every 5 seconds
    }
    delay(500);
    
    CardID = "";
    getData = "";
    Link = "";
    http.end();  //Close connection
	}

	void nemas() {
		if (digitalRead(but1Pin)!=0) {
			}	
			while (digitalRead(but1Pin)) {
				}
		   	break;
		if (digitalRead(but2Pin)!=0) {
			}	
			while (digitalRead(but2Pin)) {
				}
		   	break;
		if (digitalRead(but3Pin)!=0) {
			}	
			while (digitalRead(but3Pin)) {
				}
		   	break;
		if (digitalRead(but4Pin)!=0) {
			}	
			while (digitalRead(but4Pin)) {
				}
		   	break;
		if (digitalRead(but4Pin)!=0) {
			}	
			while (digitalRead(but4Pin)) {
				}
		   	break;
		}
	
	void mensageminicial(){
	  lcd.init(); 
	  lcd.backlight();
	  lcd.home();
	  lcd.setCursor(4, 0);
	  lcd.print(-=LUCINA=-);
	  delay(3000);
	  lcd.backlight(LOW);
	}
