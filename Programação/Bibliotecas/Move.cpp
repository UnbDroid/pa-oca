#include <Move.h>

void moveAll(int potencia) {
  motorLeft.fwd(potencia);
  motorRight.fwd(potencia);
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
  stopAll();

}

void FowardCm(int potencia, int distancia) {
  stopAll();

}

void RevCm(int potencia, int distancia) {
  stopAll();

}
