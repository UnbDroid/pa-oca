#include <Move.h>

void moveAll(int potencia) {
  motorLeft.fwd(potencia);
  motorRight.fwd(potencia);
}

void moveRevAll(int potencia) {
  motorLeft.rev(potencia);
  motorRight.rev(potencia);
}


void stopAll() {
  motorRight.stop();
  motorLeft.stop();
}

void turnClockwise(int potencia) {
  stopAll();
  motorLeft.fwd(potencia);
  motorRight.rev(potencia);
}

void turnAnticlockwise(int potencia) {
  stopAll();
  motorRight.fwd(potencia);
  motorLeft.rev(potencia);
}

void turnDegrees(int potencia, int graus, int direcao) {
  int c = DIAMETER*PI;
  int andar = (GIRO*WDIST*graus)/c;
  int countLeft = 0, countRight = 0;

  if (direcao == HORARIO) {
    motorRight.stop();
    motorLeft.fwd(potencia);
    while(countLeft!=andar) {
      countLeft = motorLeft.getencCount();
    }
    stopAll();
  }

  else if (direcao == ANTIHORARIO) {
    motorLeft.stop();
    motorRight.fwd(potencia);
    while(countRight!=andar) {
      countRight = motorRight.getencCount();
    }
    stopAll();
  }
  else {
    //error
  }
  stopAll();
}

void FowardCm(int potencia, int distancia) {

  int countLeft = 0;
  int c = DIAMETER*PI;
  int andar = (distancia*GIRO)/c;

  moveAll(potencia);

  while(countLeft!=andar) {
    countLeft = motorLeft.getencCount();
  }

  stopAll();
}

void RevCm(int potencia, int distancia) {
  int countLeft = 0;
  int c = DIAMETER*PI;
  int andar = (distancia*GIRO)/c;

  moveRevAll(potencia);

  while(countLeft!=andar) {
    countLeft = motorLeft.getencCount();
  }

  stopAll();
}
