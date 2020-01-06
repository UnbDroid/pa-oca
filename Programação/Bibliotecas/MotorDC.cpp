#include <Arduino.h>
#include <MotorDC.h>

//Função do Construtor.
MotorDC::MotorDC(int pinA, int pinB, int pinPwm){

    //Setando os atributos da classe com os valores passado pela função.
    this->pinA = pinA;
    this->pinB = pinB; 
    this->pinPwm = pinPwm;

    //Setando os pinos com OUTPUT.
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
    pinMode(pinPwm, OUTPUT);
    
}

//Função do Destrutor.
MotorDC::~MotorDC(){}


//Função que anda para frente.
void MotorDC::fwd(int pot){

    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, LOW);
    analogWrite(pinPwm, pot);

}

//Função que anda para trás.
void MotorDC::rev(int pot){

    digitalWrite(pinA, LOW);
    digitalWrite(pinB, HIGH);
    analogWrite(pinPwm, pot);
   
}

//Função de parada.

void MotorDC::stop(){
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, LOW);
}