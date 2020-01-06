/*Código de teste da biblioteca nos motores.*/

#include <Arduino.h>
#include <MotorDC.h>
#include <Ldr.h>

//Criando os objetos dos motores.
MotorDC motorLeft (12, 11, 10);
MotorDC motorRight (7, 6, 5);

//Criando os objetos dos LDR's.
Ldr ldrLeft (A0, 600);

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);

}

void loop() {

  
  
  //Motor anda para frente por 1 segundo.
  motorLeft.fwd(40);
  motorRight.fwd(40);
  delay(1000);

  //Motor anda para trás por 1 segundo.
  motorLeft.rev(40);
  motorRight.rev(40);
  delay(1000);

  //Motores param por 1 segundo.
  motorRight.stop();
  motorLeft.stop();
  delay(1000);

  


  // int leitura = ldrLeft.filter(10);
  // Serial.println(leitura);

  if (ldrLeft.read(10)){
    digitalWrite(LED_BUILTIN, HIGH);
  }else{
    digitalWrite(LED_BUILTIN, LOW);
  }

  // Acima de 600 = preto! 


}