#ifndef CHALLENGER_H
#define CHALLENGER_H


#include <Arduino.h>
#include <Move.h>
#include <Ldr.h>
#include <Ultrassom.h>
#include <SensorColor.h>
#include <Servo.h>



void followLine(int potencia, MotorDC *motorLeft, MotorDC *motorRight, Ultrassom *ultraFront);

void decodColor();

void obstacle();

void vain();


void grab();

#endif
