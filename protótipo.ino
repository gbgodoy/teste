#include <EEPROM.h>
#include <Ultrasonic.h>             // SENSOR ULTRASONICO
#include <SPI.h>
#include <MFRC522.h>              //RFID     
#include <Wire.h>               //LCD
#include <LiquidCrystal_I2C.h>          //LCD
#include <AccelStepper.h>           //movimento dos motores

#define SS_PIN 26               //pino envio RFID
#define RST_PIN 27                //pino reset RFID
#define relePin 28                //pino do relê
#define trigPin 29                //pino do ultrasom
#define echoPin 30                //pino do ultrasom

#define led1Pin 33
#define led2Pin 34
#define led3Pin 37
#define led4Pin 35
#define led5Pin 36

#define homeX 44                //início de curso eixo X
#define homeY 45                //início de curso eixo Y
#define endY 46                 //início de curso eixo Y

#define dirPinX 48                //direção moto eixo X
#define stepPinX 49   
#define dirPinY1 50               //direção moto eixo Y
#define stepPinY1 51    
#define dirPinY2 52               //direção moto eixo Y
#define stepPinY2 53    

const int selectButton01 = 38;          //botões
const int selectButton02 = 39;          //botões
const int selectButton03 = 40;          //botões
const int selectButton04 = 41;          //botões
const int selectButton05 = 42;          //botões

#define motorInterfaceType 1

AccelStepper stepperX = AccelStepper(motorInterfaceType, stepPinX, dirPinX);
AccelStepper stepperY1 = AccelStepper(motorInterfaceType, stepPinY1, dirPinY1);
AccelStepper stepperY2 = AccelStepper(motorInterfaceType, stepPinY2, dirPinY2);

Ultrasonic sr04(trigPin, echoPin);
MFRC522 mfrc522(SS_PIN, RST_PIN);       
LiquidCrystal_I2C lcd(0x27, 16, 2);       

int distance = 0;
bool activeSession = false;
int engineProduct = 0;
int activateDistance;

void setup() {
  digitalWrite(relePin,LOW);            //motor inicia desligado
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led1Pin, OUTPUT);
  Serial.begin(9600);
  mfrc522.PCD_Init();
}

void loop() {

  distance = checkDistance();

  if (!activeSession) {
    if (distance <= activateDistance) {
      greetings();
      activeSession = true;
    }
  }

  if (activeSession) {
      engineProduct = productSelection(0, 3, 7);
      nichoSelecionado(engineProduct);
      activeSession = false;
      delay(2500);

  }

}

int checkDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return sr04.Ranging(CM);
  delay(500);
} 

void greetings() {
  for (int i = 0; i < 255; i += 5) {
    analogWrite(led1Pin, i);
    delay(30);
  }
  for (int i = 255; i > 122; i--) {
    analogWrite(led1Pin, i);
    delay(10);
  }
}

int productSelection(int button, int initialButton, int finalButton) {
  while (button == 0) {
   for (int i = initialButton; i < finalButton; i++) {
     if (digitalRead(i) == HIGH) {
       button = i;
       return i;
     }
   }
  }
}

int nichoSelecionado(int engineProduct) {

  switch (engineProduct) {

      case 1:
        stepperX.moveTo(100);
        stepperX.runToPosition();
          break;

      case 2:
        stepperX.moveTo(200);
        stepperX.runToPosition();
        break;

      case 3:
        stepperX.moveTo(300);
        stepperX.runToPosition();
        break;

      case 4:
          stepperX.moveTo(400);
      stepperX.runToPosition();
      break;

      case 5:
        stepperX.moveTo(500);
      stepperX.runToPosition();
        break;
  }
}

String validaCartao() { 
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  Serial.print("Validando Cartão:");
  String conteudo = "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();
  return conteudo;
}
