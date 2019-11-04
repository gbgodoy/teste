#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Ultrasonic.h>


#define SS_PIN 53
#define RST_PIN 49

#define pirPin 7
#define ledPin 3



MFRC522 mfrc522(SS_PIN, RST_PIN);

LiquidCrystal_I2C lcd(0x27, 16, 2);

Ultrasonic ultrassom(7,6); // define o nome do sensor(ultrassom)



void setup(){
	pinMode(pirPin, INPUT);   // pino sensor de presenÃ§a
	pinMode(ledPin, OUTPUT);  //pino ledPin
	digitalWrite(ledPin, 0);

	Serial.begin(9600);
	SPI.begin();

	mfrc522.PCD_Init();
	Serial.println("aproxime seu cartao");
int presenca = 0;

	/* config lcd */
	lcd.init();
	lcd.backlight();
	lcd.home();
	lcd.setCursor(2, 0);
	lcd.print("-= Lucina =-");
	delay(2000);
	lcd.setBacklight(LOW);
}

void loop(){


	if ( mfrc522.PICC_IsNewCardPresent()) {
		if ( mfrc522.PICC_ReadCardSerial())	{
			Serial.print("UID da Tag:");
			for (byte i = 0;i < mfrc522.uid.size; i++){
				Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
				Serial.print(mfrc522.uid.uidByte[i], HEX);
			}
			Serial.println();
			mfrc522.PICC_HaltA();  
			delay(10);
		}
	}
}