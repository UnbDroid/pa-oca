#include <Arduino.h>
#include <Move.h>
#include <math.h>

#define kp 0.05
#define ki 0.001
float time1 = millis();


//Função que move as duas rodas para a frente.
void moveAll(int _power, MotorDC *motorLeft, MotorDC *motorRight) {
  motorLeft->fwd(_power);
  motorRight->fwd(_power);
}


//Função que move as duas para frente, porém usando o PID.
void moveAllpid(int _power, MotorDC *motorLeft, MotorDC *motorRight, float *soma, float *error, float giro) {
  float powerLeft;
  float powerRight;
//  float lastError = error[0];
  float lastT = error[1];
  float deltaT;
//  float deltaE;

  float mLeft = motorLeft->getCount();
  float mRight = motorRight->getCount();
  error[0] = (mLeft - mRight) - giro; // diferença entre os encoderes sendo o error atual
  error[1] = millis();
  //Serial.print("EncodL:");
  //Serial.println(motorLeft->getCount());
  //Serial.println(mLeft);
  //Serial.print("EncodR:");
  //Serial.println(motorRight->getCount());
  //Serial.println(mRight);


  deltaT = (error[1] - lastT)/1000;
//  deltaE = abs(error[0] - lastError);

  //Serial.print("Delta :");
  //Serial.println(deltaT);
  //Serial.print("Erro :");
  //Serial.println(error[0]);

  *soma = (*soma)*0.6 + error[0]*deltaT;

  if((*soma)*ki > 10){
    *soma = 10/ki;
  }
  else if((*soma)*ki < -10){
    *soma = -10/ki;
  }

  powerLeft = abs(_power);
  powerRight = abs(_power) + (error[0]*kp) + (*soma)*ki;

  //Serial.print("Pot :");
  //Serial.println(powerRight);
  //Serial.print("Soma :");
  //Serial.println(*soma);

  motorLeft->fwd(powerLeft);
  motorRight->fwd(powerRight);


  if(_power < 0){

    if((error[1] - time1) > 3500){
      motorLeft->rev(powerLeft);
      motorRight->rev(powerRight);
    } else {
      motorLeft->rev(50);
      motorRight->rev(50);
    }

  }else{
    if((error[1] - time1) > 3500){
      motorLeft->fwd(powerLeft);
      motorRight->fwd(powerRight);
    } else {
      motorLeft->fwd(50);
      motorRight->fwd(50);
    }
  }


  ////Serial.print("error:");
  ////Serial.println()
  ////Serial.print("potLeft");
  ////Serial.println(potLeft);
  ////Serial.print("potRight");
  ////Serial.println(potRight);
  ////Serial.print("Soma:");
  ////Serial.println((*soma));




  //delay(80);
  //stopAll(motorLeft,motorRight);
}


//Função que move as duas rodas para trás.
void moveRevAll(int _power, MotorDC *motorLeft, MotorDC *motorRight) {
  motorLeft->rev(_power);
  motorRight->rev(_power);
}


//Função que para as duas rodas.
void stopAll(MotorDC *motorLeft, MotorDC *motorRight) {
  motorRight->stop();
  motorLeft->stop();
}


//Função que gira o robô no sentido horário.
void turnClockwise(int _power, MotorDC *motorLeft, MotorDC *motorRight) {
  stopAll(motorLeft, motorRight);
  motorLeft->fwd(_power);
  motorRight->rev(_power);
  delay(120);
  stopAll(motorLeft,motorRight);
}

//Função que gira o robô no sentido antihorário.
void turnAnticlockwise(int _power,  MotorDC *motorLeft, MotorDC *motorRight) {
  stopAll(motorLeft, motorRight);
  motorRight->fwd(_power);
  motorLeft->rev(_power);
  delay(120);
  stopAll(motorLeft,motorRight);
}

//Função que gira o robô de acordo com o graus.
//dir = HORARIO ou ANTIHORARIO
void turnDegrees(int _power, int _degree, int _clock, MotorDC *motorLeft, MotorDC *motorRight) {
  int c = DIAMETER*3.14;
  int move = (GIRO*(WDIST*3.14*2)*((float) _degree/360))/c;
  int countLeftInitial = motorLeft->getCount();
  int countLeftUpdate = motorLeft->getCount();
  int countRightInitial = motorRight->getCount();
  int countRightUpdate = motorRight->getCount();

  if (_clock == HORARIO) {
    motorLeft->fwd(_power);
    motorRight->rev(_power);
    while((countLeftUpdate - countLeftInitial) < move ) {
      countLeftUpdate = motorLeft->getCount();
      Serial.println("Counter L deg");
      Serial.println(countLeftUpdate);
    }
    stopAll(motorLeft, motorRight);
  }

  else if (_clock == ANTIHORARIO) {
    motorRight->fwd(_power);
    motorLeft->rev(_power);
    while((countRightUpdate - countRightInitial) < move) {
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

//Andar para frente uma certa distância.
void FowardCm(int _power, int _distance, MotorDC *motorLeft, MotorDC *motorRight) {

  int countLeftInitial = motorLeft->getCount();
  int countLeftUpdate = motorLeft->getCount();
  int c = DIAMETER*PI;
  int move = (_distance*GIRO)/c;

  moveAll(_power, motorLeft, motorRight);

  while((countLeftUpdate - countLeftInitial) < move ) {
    moveAll(_power, motorLeft, motorRight);
    countLeftUpdate = motorLeft->getCount();
    ////Serial.println("Counter L fwd");
    ////Serial.println(countLeftUpdate);
    ////Serial.println(andar);
    ////Serial.println(countLeftInitial);
  }

  stopAll(motorLeft, motorRight);
}


//Andar para trás uma certa distância
void RevCm(int _power, int _distance, MotorDC *motorLeft, MotorDC *motorRight) {
  int countLeft = 0;
  int c = DIAMETER*PI;
  int move = (_distance*GIRO)/c;

  moveRevAll(_power, motorLeft, motorRight);

  while(countLeft < move) {
    countLeft = motorLeft->getCount();
  }

  stopAll(motorLeft, motorRight);
}
