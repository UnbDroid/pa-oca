#include <Arduino.h>
#include <Move.h>

#define kp 0.05
#define ki 0.001
float time1 = millis();

void moveAll(int potencia, MotorDC *motorLeft, MotorDC *motorRight) {
  motorLeft->fwd(potencia);
  motorRight->fwd(potencia);  
}

void moveAllpid(int _potencia, MotorDC *motorLeft, MotorDC *motorRight, float *soma, float *error, float giro) {
  float potLeft;
  float potRight;
  float lastError = error[0];
  float lastT = error[1];
  float deltaT;
  //float deltaE;

  float mLeft = motorLeft->getCount();
  float mRight = motorRight->getCount();
  error[0] = (mLeft - mRight) - giro; // diferença entre os encoderes sendo o error atual
  error[1] = millis();
  Serial.print("EncodL:");
  Serial.println(motorLeft->getCount());
  Serial.println(mLeft);
  Serial.print("EncodR:");
  Serial.println(motorRight->getCount());
  Serial.println(mRight);
  

  deltaT = (error[1] - lastT)/1000;
  //deltaE = error[0] - lastError;

  Serial.print("Delta :");
  Serial.println(deltaT);
  Serial.print("Erro :");
  Serial.println(error[0]);

  *soma += error[0]*deltaT; 

  if((*soma)*ki > 10){
    *soma = 10/ki;
  }
  else if((*soma)*ki < -10){
    *soma = -10/ki;
  }

  potLeft = abs(_potencia);
  potRight = abs(_potencia) + (error[0]*kp) + (*soma)*ki;

  Serial.print("Pot :");
  Serial.println(potRight);
  Serial.print("Soma :");
  Serial.println(*soma);

  motorLeft->fwd(potLeft);
  motorRight->fwd(potRight);

  
  if(_potencia < 0){

    if((error[1] - time1) > 3500){
      motorLeft->rev(potLeft);
      motorRight->rev(potRight);
    } else {
      motorLeft->rev(50);
      motorRight->rev(50);
    }

  }else{  
    if((error[1] - time1) > 3500){
      motorLeft->fwd(potLeft);
      motorRight->fwd(potRight);
    } else {
      motorLeft->fwd(50);
      motorRight->fwd(50);
    }
  }
  

  //Serial.print("error:");
  //Serial.println()
  //Serial.print("potLeft");
  //Serial.println(potLeft);
  //Serial.print("potRight");
  //Serial.println(potRight);
  //Serial.print("Soma:");
  //Serial.println((*soma));

  


  //delay(80);
  //stopAll(motorLeft,motorRight);
}

void moveRevAll(int potencia, MotorDC *motorLeft, MotorDC *motorRight) {
  motorLeft->rev(potencia);
  motorRight->rev(potencia); 
}



void stopAll(MotorDC *motorLeft, MotorDC *motorRight) {
  motorRight->stop();
  motorLeft->stop();
}

void turnClockwise(int potencia, MotorDC *motorLeft, MotorDC *motorRight) {
  stopAll(motorLeft, motorRight);
  motorLeft->fwd(potencia);
  motorRight->rev(potencia+40);
  delay(120);
  stopAll(motorLeft,motorRight);
}

void turnAnticlockwise(int potencia,  MotorDC *motorLeft, MotorDC *motorRight) {
  stopAll(motorLeft, motorRight);
  motorRight->fwd(potencia+16);
  motorLeft->rev(potencia+25);
  delay(120);
  stopAll(motorLeft,motorRight);
}

void turnDegrees(int potencia, int graus, int direcao, MotorDC *motorLeft, MotorDC *motorRight) {
  int c = DIAMETER*3.14;
  int andar = (GIRO*(WDIST*3.14*2)*((float) graus/360))/c;
  int countLeftInitial = motorLeft->getCount();
  int countLeftUpdate = motorLeft->getCount();
  int countRightInitial = motorRight->getCount();
  int countRightUpdate = motorRight->getCount();

  if (direcao == HORARIO) {
    motorRight->stop();
    motorLeft->fwd(potencia+16);
    while((countLeftUpdate - countLeftInitial) < andar) {
      countLeftUpdate = motorLeft->getCount();
      Serial.println("Counter L deg");
      Serial.println(countLeftUpdate);
    }
    stopAll(motorLeft, motorRight);
  }

  else if (direcao == ANTIHORARIO) {
    motorLeft->stop();
    motorRight->fwd(potencia+16);
    while((countRightUpdate - countRightInitial) < andar) {
      countRightUpdate = motorRight->getCount();
      Serial.println("Counter R");
      Serial.println(countRightUpdate);
    }
    stopAll(motorLeft, motorRight);
  }
  else {
    //error
  }
  stopAll(motorLeft, motorRight);
}

void FowardCm(int potencia, int distancia, MotorDC *motorLeft, MotorDC *motorRight) {

  int countLeftInitial = motorLeft->getCount();
  int countLeftUpdate = motorLeft->getCount();
  int c = DIAMETER*PI;
  int andar = (distancia*GIRO)/c;

  moveAll(potencia, motorLeft, motorRight);

  while((countLeftUpdate - countLeftInitial) < andar) {
    moveAll(potencia, motorLeft, motorRight);
    countLeftUpdate = motorLeft->getCount();
    //Serial.println("Counter L fwd");
    //Serial.println(countLeftUpdate);
    //Serial.println(andar);
    //Serial.println(countLeftInitial);
  }

  stopAll(motorLeft, motorRight);
}

void RevCm(int potencia, int distancia, MotorDC *motorLeft, MotorDC *motorRight) {
  int countLeft = 0;
  int c = DIAMETER*PI;
  int andar = (distancia*GIRO)/c;

  moveRevAll(potencia, motorLeft, motorRight);

  while(countLeft < andar) {
    countLeft = motorLeft->getCount();
  }

  stopAll(motorLeft, motorRight);
}
