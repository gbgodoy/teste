#pragma GCC push_options
#pragma GCC optimize ("Os")
#include <core.h> 
#include <cpu.h>
#include <TimerOne.h>
#include <TimerThree.h>
#pragma GCC pop_options
CPU &cpu = Cpu;
TimerOne &timer1 = Timer1;
TimerThree &timer3 = Timer3;
void peripheral_setup () {}
void peripheral_loop() {}
//===============================================================================================================//
#include <EEPROM.h>
#include <LiquidCrystal.h>

#define botao1 22	//credito
#define botao2 23	//compra1
#define botao3 24	//compra2
#define botao4 25	//compra3
#define botao5 26	//compra4
#define botao6 27	//compra5
#define botao7 28	//compra6
#define botao8 29	//compra7


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int credito = EEPROM.read(0);


//================================================ VOID SETUP ===================================================//
void setup () {
peripheral_setup();

//inicialização LCD -------------------------------------------
lcd.begin(16, 2);
lcd.clear();
lcd.setCursor(4, 0);
lcd.print("Creditos");
lcd.setCursor(7, 1);
lcd.print(credito);

//------------------------------------------------------------------

pinMode(botao1,INPUT_PULLUP);     //modo de entrada do botão - botão de compra
pinMode(botao2,INPUT_PULLUP);    
pinMode(botao3,INPUT_PULLUP);     
pinMode(botao4,INPUT_PULLUP);    
pinMode(botao5,INPUT_PULLUP);     
pinMode(botao6,INPUT_PULLUP);    
pinMode(botao7,INPUT_PULLUP);    
pinMode(botao8,INPUT_PULLUP);    

Serial.begin(9600);
Serial.println(credito);
delay(400);


}
//================================================ VOID LOOP ===================================================//
void loop() {
peripheral_loop();

//---------------------------------------------------------------------------- BOTÃO CRÉDITO ---------------------------------------------------------------------------//
if (digitalRead(botao1)!=0) {
credito++; EEPROM.write(0,credito);
delay(100);     //delay entre pulsos
Serial.println(EEPROM.read(0));
lcd.clear();
lcd.setCursor(4, 0);
lcd.print("Creditos");
lcd.setCursor(7, 1);
lcd.print(credito);

}
while (digitalRead(botao1) ) {
}
delay(10);
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------- BOTÃO COMPRA ---------------------------------------------------------------------------//
if (digitalRead(botao2)!=0) {
if (EEPROM.read(0)>0) {
credito--; EEPROM.write(0,credito);
delay(100);     //delay entre pulsos
Serial.println(EEPROM.read(0));
lcd.clear();
lcd.setCursor(4, 0);
lcd.print("Creditos");
lcd.setCursor(7, 1);
lcd.print(credito);
}
}
while (digitalRead(botao2) ) {
}
delay(10);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

}
