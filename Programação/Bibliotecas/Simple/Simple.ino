#include <Arduino.h>
#include "Move.h"
#include "MotorDC.h"

void fwd(int pot, int pinA, int pinB, int pinPwm){
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, LOW);
    analogWrite(pinPwm, pot);
}

void rev(int pot, int pinA, int pinB, int pinPwm){
    digitalWrite(pinA, LOW);
    digitalWrite(pinB, HIGH);
    analogWrite(pinPwm, pot);
   
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  pinMode(A6, INPUT);
  pinMode(A3, INPUT);
  pinMode(51, OUTPUT);
  pinMode(49, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  if(analogRead(A6) > 200 && analogRead(A3) > 200) {
    rev(40, 48, 49, 3);
    rev(40, 46, 51, 7);
    Serial.println("A");
  }
  else if(analogRead(A6) > 200) {
    rev(40, 48, 49, 3);
    fwd(40, 46, 51, 7);
    Serial.println("B");
  }
  else if(analogRead(A3) > 200) {
    fwd(40, 48, 49, 3);
    rev(40, 46, 51, 7);
    Serial.println("C");
  } else {
    fwd(40, 48, 49, 3);
    fwd(40, 46, 51, 7);
    Serial.println("D");
  }
}
